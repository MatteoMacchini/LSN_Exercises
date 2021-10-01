/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
#include <stdlib.h>     // srand, rand: to generate random number
#include <iostream>     // cin, cout: Standard Input/Output Streams Library
#include <fstream>      // Stream class to both read and write from/to files.
#include <cmath>        // rint, pow
#include "MolDyn_NVE.h"

using namespace std;

    //==================================================================================
    //==================================================================================

int main(){
    
    Input(); //Inizialization
    
    int nblocks = 100;
    int L = (int)nstep/nblocks;
    int nconf = 1;
    
    //==================================================================================
    //================================== Equilibration =================================
    //==================================================================================
    
    /*for(int istep=1; istep <= nstep; ++istep){
       Move();           //Move particles with Verlet algorithm
       if(istep%iprint == 0) cout << "Number of time-steps: " << istep << endl;
       if(istep%10 == 0){
          Measure();     //Properties measurement
     //     ConfXYZ(nconf);//Write actual configuration in XYZ format //Commented to avoid "filesystem full"!
          nconf += 1;
       }
    } */
    
    double ave_temp=0., av2_temp=0., ave_ekin=0., av2_ekin=0., ave_epot=0., av2_epot=0., ave_etot=0., av2_etot=0.;
    double ave_g[100];
    double av2_g[100];
    
    for (int i=0; i<100; i++) {
        ave_g[i]=0.;
        av2_g[i]=0.;
    }
    
    ofstream T("ave_temp.out");
       if (!T) cerr << "Non posso creare il file ave_temp.out" << endl;
           
    ofstream Ek("ave_ekin.out");
       if (!Ek) cerr << "Non posso creare il file ave_ekin.out" << endl;

    ofstream Ep("ave_epot.out");
       if (!Ep) cerr << "Non posso creare il file ave_epot.out" << endl;

    ofstream Et("ave_etot.out");
       if (!Et) cerr << "Non posso creare il file ave_etot.out" << endl;
    
    ofstream Gave("gave.out");
       if (!Et) cerr << "Non posso creare il file gave.out" << endl;
    
    for (int iblock=1; iblock <= nblocks; ++iblock) {
        double sum_temp=0., sum_ekin=0., sum_epot=0., sum_etot=0.;
        for (int j=1; j<=L; ++j) {
            Move(); //Move particles with Verlet algorithm
            if (j%10 == 0) {
                Measure();     //Properties measurement
    //          ConfXYZ(nconf); //Write actual configuration in XYZ format //Commented to avoid "filesystem full"!
                sum_temp += stima_temp;
                sum_ekin += stima_kin;
                sum_epot += stima_pot;
                sum_etot += stima_etot;
                nconf += 1;
            }
        }
        
        if(iblock%10==0) cout << "Number of blocks: " << iblock << ",   Number of time-steps: " << (iblock)*L << endl;
        
        ave_temp += sum_temp*10./L; // moltiplico per 10 perchè il numero di misure in ogni blocco non è L, ma è L/10
        av2_temp += pow(sum_temp*10./L,2);
        ave_ekin += sum_ekin*10./L;
        av2_ekin += pow(sum_ekin*10./L,2);
        ave_epot += sum_epot*10./L;
        av2_epot += pow(sum_epot*10./L,2);
        ave_etot += sum_etot*10./L;
        av2_etot += pow(sum_etot*10./L,2);
        
        T << iblock << " " << ave_temp/(iblock) << " " << err(ave_temp,av2_temp,iblock) << endl;
        Ek << iblock << " " << ave_ekin/(iblock) << " " << err(ave_ekin,av2_ekin,iblock) << endl;
        Ep << iblock << " " << ave_epot/(iblock) << " " << err(ave_epot,av2_epot,iblock) << endl;
        Et << iblock << " " << ave_etot/(iblock) << " " << err(ave_etot,av2_etot,iblock) << endl;
        
        // g(r)
        for (int k=igofr; k<n_props; ++k){
            double r = ((double)k-(double)igofr)*bin_size;
            double gdir = 3.*10.*(double)bins[k-igofr]/(4.*M_PI*rho*(double)npart*(double)L*(pow(r+bin_size,3)-pow(r,3))); // moltiplico per 10 perchè il numero di misure in ogni blocco non è L, ma è L/10
            ave_g[k-igofr] += gdir;
            av2_g[k-igofr] += gdir*gdir;
            if(iblock==nblocks) Gave << ((double)k-(double)igofr+0.5)*bin_size << " " << ave_g[k-igofr]/(double)iblock << " " << err(ave_g[k-igofr],av2_g[k-igofr],iblock) << endl;
        }
        
        for(int i=0; i<nbins; i++) bins[i]=0.;
        
    }
    
    T.close();
    Ek.close();
    Ep.close();
    Et.close();
    Gave.close();
    
    ConfFinal();         //Write final configuration to restart
    
    return 0;
}

    //==================================================================================
    //==================================================================================

void Input(void) { //Prepare all stuff for the simulation
    ifstream ReadInput,ReadConf;
    double ep, ek, pr, et, vir;

    cout << "Classic Lennard-Jones fluid        " << endl;
    cout << "Molecular dynamics simulation in NVE ensemble  " << endl << endl;
    cout << "Interatomic potential v(r) = 4 * [(1/r)^12 - (1/r)^6]" << endl << endl;
    cout << "The program uses Lennard-Jones units " << endl;

    seed = 1;    //Set seed for random numbers
    srand(seed); //Initialize random number generator
  
    ReadInput.open("input.dat"); //Read input

    ReadInput >> restart;

    ReadInput >> temp;

    ReadInput >> npart;
    cout << "Number of particles = " << npart << endl;

    ReadInput >> rho;
    cout << "Density of particles = " << rho << endl;
    vol = (double)npart/rho;
    cout << "Volume of the simulation box = " << vol << endl;
    box = pow(vol,1.0/3.0);
    cout << "Edge of the simulation box = " << box << endl;

    ReadInput >> rcut;
    ReadInput >> delta;
    ReadInput >> nstep;
    ReadInput >> iprint;

    cout << "The program integrates Newton equations with the Verlet method " << endl;
    cout << "Time step = " << delta << endl;
    cout << "Number of steps = " << nstep << endl << endl;
    ReadInput.close();

    //Prepare array for measurements
    iv = 0; //Potential energy
    ik = 1; //Kinetic energy
    ie = 2; //Total energy
    it = 3; //Temperature
    n_props = 4; //Number of observables
    
    //measurement of g(r)
    igofr = 4;
    nbins = 100;
    n_props = n_props + nbins;
    bin_size = (box/2.0)/(double)nbins;
    
    for(int i=0; i<nbins; i++) bins[i]=0.;

    //Read initial configuration
    cout << "Read initial configuration from file config.0 " << endl << endl;
    ReadConf.open("config.0");
    for (int i=0; i<npart; ++i) {
        ReadConf >> x[i] >> y[i] >> z[i];
        x[i] = x[i] * box;
        y[i] = y[i] * box;
        z[i] = z[i] * box;
    }
    ReadConf.close();

    if (restart == false) {
        //Prepare initial velocities
        cout << "Prepare random velocities with center of mass velocity equal to zero " << endl << endl;
        double sumv[3] = {0.0, 0.0, 0.0};
        for (int i=0; i<npart; ++i) {
            vx[i] = rand()/double(RAND_MAX) - 0.5;
            vy[i] = rand()/double(RAND_MAX) - 0.5;
            vz[i] = rand()/double(RAND_MAX) - 0.5;

            sumv[0] += vx[i];
            sumv[1] += vy[i];
            sumv[2] += vz[i];
        }
        for (int idim=0; idim<3; ++idim) sumv[idim] /= (double)npart;
        double sumv2 = 0.0, fs;
        for (int i=0; i<npart; ++i) {
            vx[i] = vx[i] - sumv[0];
            vy[i] = vy[i] - sumv[1];
            vz[i] = vz[i] - sumv[2];

            sumv2 += vx[i]*vx[i] + vy[i]*vy[i] + vz[i]*vz[i];
        }
        sumv2 /= (double)npart;

        fs = sqrt(3 * temp / sumv2);   // fs = velocity scale factor
        for (int i=0; i<npart; ++i) {
            vx[i] *= fs;
            vy[i] *= fs;
            vz[i] *= fs;

            xold[i] = Pbc(x[i] - vx[i] * delta);
            yold[i] = Pbc(y[i] - vy[i] * delta);
            zold[i] = Pbc(z[i] - vz[i] * delta);
        }
    }
    
    else {
        // Read old configuration
        cout << "Read old configuration from file old.0 " << endl << endl;
        ReadConf.open("old.0");
        for (int i=0; i<npart; ++i) {
            ReadConf >> xold[i] >> yold[i] >> zold[i];
            xold[i] = xold[i] * box;
            yold[i] = yold[i] * box;
            zold[i] = zold[i] * box;
        }
        ReadConf.close();
        
        // First step of Verlet algorithm
        double xnew, ynew, znew, fx[m_part], fy[m_part], fz[m_part];
        
        for (int i=0; i<npart; ++i) { // Force acting on particle i
            fx[i] = Force(i,0);
            fy[i] = Force(i,1);
            fz[i] = Force(i,2);
        }
        
        for (int i=0; i<npart; ++i) { // Verlet integration scheme

            xnew = Pbc( 2.0 * x[i] - xold[i] + fx[i] * pow(delta,2) );
            ynew = Pbc( 2.0 * y[i] - yold[i] + fy[i] * pow(delta,2) );
            znew = Pbc( 2.0 * z[i] - zold[i] + fz[i] * pow(delta,2) );

            xold[i] = x[i];
            yold[i] = y[i];
            zold[i] = z[i];

            x[i] = xnew;
            y[i] = ynew;
            z[i] = znew;
        }
        
        /* double sumv2 = 0.0, fs;
        // Computing the velocities at time t + dt/2
        for (int i=0; i<npart; ++i) {
            vx[i] = (x[i]-xold[i])/delta;
            vy[i] = (y[i]-yold[i])/delta;
            vz[i] = (z[i]-zold[i])/delta;
            sumv2 += vx[i]*vx[i] + vy[i]*vy[i] + vz[i]*vz[i];
        }
        sumv2 /= (double)npart;
        
        fs = sqrt(3*temp/sumv2);
        for (int i=0; i<npart; ++i) {
            vx[i] *= fs;
            vy[i] *= fs;
            vz[i] *= fs;

            xold[i] = Pbc(x[i] - vx[i] * delta);
            yold[i] = Pbc(y[i] - vy[i] * delta);
            zold[i] = Pbc(z[i] - vz[i] * delta);
        } */
    }
    
    return;
}


void Move(void){ //Move particles with Verlet algorithm
    double xnew, ynew, znew, fx[m_part], fy[m_part], fz[m_part];

    for (int i=0; i<npart; ++i) { //Force acting on particle i
        fx[i] = Force(i,0);
        fy[i] = Force(i,1);
        fz[i] = Force(i,2);
    }

    for (int i=0; i<npart; ++i) { //Verlet integration scheme

        xnew = Pbc( 2.0 * x[i] - xold[i] + fx[i] * pow(delta,2) );
        ynew = Pbc( 2.0 * y[i] - yold[i] + fy[i] * pow(delta,2) );
        znew = Pbc( 2.0 * z[i] - zold[i] + fz[i] * pow(delta,2) );

        vx[i] = Pbc(xnew - xold[i])/(2.0 * delta);
        vy[i] = Pbc(ynew - yold[i])/(2.0 * delta);
        vz[i] = Pbc(znew - zold[i])/(2.0 * delta);

        xold[i] = x[i];
        yold[i] = y[i];
        zold[i] = z[i];

        x[i] = xnew;
        y[i] = ynew;
        z[i] = znew;
    }
    return;
}

double Force (int ip, int idir) { //Compute forces as -Grad_ip V(r)
    double f=0.0;
    double dvec[3], dr;

    for (int i=0; i<npart; ++i) {
        if (i != ip) {
            dvec[0] = Pbc( x[ip] - x[i] );  // distance ip-i in pbc
            dvec[1] = Pbc( y[ip] - y[i] );
            dvec[2] = Pbc( z[ip] - z[i] );

            dr = dvec[0]*dvec[0] + dvec[1]*dvec[1] + dvec[2]*dvec[2];
            dr = sqrt(dr);

            if (dr < rcut) {
                f += dvec[idir] * (48.0/pow(dr,14) - 24.0/pow(dr,8)); // -Grad_ip V(r)
            }
        }
    }
  
    return f;
}

void Measure(){ //Properties measurement
    int bin;
    double v, t, vij;
    double dx, dy, dz, dr;
    ofstream Epot, Ekin, Etot, Temp;

    Epot.open("output_epot.dat",ios::app);
    Ekin.open("output_ekin.dat",ios::app);
    Temp.open("output_temp.dat",ios::app);
    Etot.open("output_etot.dat",ios::app);

    v = 0.0; //reset observables
    t = 0.0;

    //cycle over pairs of particles
    for (int i=0; i<npart-1; ++i){
        for (int j=i+1; j<npart; ++j){

            dx = Pbc( xold[i] - xold[j] ); // here I use old configurations [old = r(t)]
            dy = Pbc( yold[i] - yold[j] ); // to be compatible with EKin which uses v(t)
            dz = Pbc( zold[i] - zold[j] ); // => EPot should be computed with r(t)

            dr = dx*dx + dy*dy + dz*dz;
            dr = sqrt(dr);
            
            //update of the histogram of g(r)
            if (dr <= box/2.) {
                bin = (int)(dr/bin_size);
                bins[bin] += 2.;
            }

            if(dr < rcut){
                vij = 4.0/pow(dr,12) - 4.0/pow(dr,6);
                //Potential energy
                v += vij;
            }
        }
    }

    //Kinetic energy
    for (int i=0; i<npart; ++i) t += 0.5 * (vx[i]*vx[i] + vy[i]*vy[i] + vz[i]*vz[i]);
   
    stima_pot = v/(double)npart; //Potential energy per particle
    stima_kin = t/(double)npart; //Kinetic energy per particle
    stima_temp = (2.0 / 3.0) * t/(double)npart; //Temperature
    stima_etot = (t+v)/(double)npart; //Total energy per particle
    
    Epot << stima_pot  << endl;
    Ekin << stima_kin  << endl;
    Temp << stima_temp << endl;
    Etot << stima_etot << endl;

    Epot.close();
    Ekin.close();
    Temp.close();
    Etot.close();

    return;
}


void ConfFinal(void){ //Write final configuration
    ofstream WriteConf;

    cout << endl << "Print old configuration to file old.final " << endl << endl;
    WriteConf.open("old.final");
    for (int i=0; i<npart; ++i) {
        WriteConf << xold[i]/box << "   " <<  yold[i]/box << "   " << zold[i]/box << endl;
    }
    WriteConf.close();
    
    cout << "Print final configuration to file config.final " << endl << endl;
    WriteConf.open("config.final");
    for (int i=0; i<npart; ++i) {
        WriteConf << x[i]/box << "   " <<  y[i]/box << "   " << z[i]/box << endl;
    }
    WriteConf.close();

    return;
}

void ConfXYZ(int nconf){ //Write configuration in .xyz format
    ofstream WriteXYZ;

    WriteXYZ.open("frames/config_" + to_string(nconf) + ".xyz");
    WriteXYZ << npart << endl;
    WriteXYZ << "This is only a comment!" << endl;
    for (int i=0; i<npart; ++i) {
        WriteXYZ << "LJ  " << Pbc(x[i]) << "   " <<  Pbc(y[i]) << "   " << Pbc(z[i]) << endl;
    }
    WriteXYZ.close();
}

double Pbc(double r){  //Algorithm for periodic boundary conditions with side L=box
    return r - box * rint(r/box);
}

double err (double med, double med2, int n) {
    if (n==0) return 0;
    else return sqrt((med2/(n) - pow(med/(n),2))/n);
}

/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
