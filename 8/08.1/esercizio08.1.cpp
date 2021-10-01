#include <iostream>
#include <fstream>
#include <string>
#include "random.h"
#include "funzioni.h"
#include "metropolis.h"
#include "funzionebase.h"


using namespace std;
 
int main (int argc, char *argv[]){
    
    Random * rnd = new Random();
    int seed[4];
    int p1, p2;
    ifstream Primes("Primes");
    if (Primes.is_open()){
        Primes >> p1 >> p2 ;
    } else cerr << "PROBLEM: Unable to open Primes" << endl;
    Primes.close();

    ifstream input("seed.in");
    string property;
    if (input.is_open()){
        while ( !input.eof() ){
            input >> property;
            if( property == "RANDOMSEED" ){
                input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
                rnd->SetRandom(seed,p1,p2);
            }
        }
        input.close();
    } else cerr << "PROBLEM: Unable to open seed.in" << endl;
    
    double mu = 0.806, sigma = 0.619;
    double mu_min = 0.76, mu_max = 0.831;
    double sigma_min = 0.58, sigma_max = 0.651;
    
    mu = mu_min;
    sigma = sigma_min;

    double x = 1.;
    double step = 6.*sigma; // step of the uniform transition probability T(x|y)
    //double step = 5.3; // step for minimal mu and sigma
    double V = pow(x,4)-2.5*pow(x,2);
    
    Psi_Trial * Psi_T = new Psi_Trial(mu, sigma);
    Metropolis * MTR = new Metropolis(step, 0., x, Psi_T, rnd);
    
    cout << "Single quantum particle in a one dimensional space - Monte Carlo simulation" << endl;
    cout << "External potential: V(x) = x^4 - 5/2 * x^2" << endl << endl;
    
    int N = 300;
    
    int Nstep = 500000;
     
    //===============================================================================
    //================================ Equilibration ================================
    //===============================================================================
     
    ofstream fout("eq.dat");
    if (!fout) cerr << "Non posso creare il file eq.dat" << endl;
    
    ofstream var("var.dat");
    if (!var) cerr << "Non posso creare il file var.dat" << endl;
    
    for (int i=0; i<N; ++i) {
        MTR->Step_Unif();
        fout << i+1 << " " << abs(MTR->Get_Pos()) << endl;
     }
    cout << endl << "Equilibration" << endl;
    cout << "Acception rate: " << double(MTR->Get_Acception())/N << endl << endl;
    
    fout.close();
     
    //===============================================================================
    //============================= Minimizing mu, sigma ============================
    //===============================================================================
    
    double ene = 0., stima_ene = 0.;
    for (double imu = mu_min; imu <= mu_max; imu += 0.001) {
        for (double isigma = sigma_min; isigma <= sigma_max; isigma += 0.001) {
            Psi_T->Set_Mu(imu);
            Psi_T->Set_Sigma(isigma);
            Metropolis Metro(step, 0., x, Psi_T, rnd);
            for (int i=0; i<N; ++i) {
                Metro.Step_Unif();
                fout << i+1 << " " << abs(MTR->Get_Pos()) << endl;
            }
            for (int i=0; i<Nstep; ++i) {
                Metro.Step_Unif();
                x = Metro.Get_Pos();
                stima_ene += -0.5*Psi_T->Eval_sec(x)/Psi_T->Eval(x)+pow(x,4)-2.5*pow(x,2);
            }
            stima_ene = stima_ene/double(Nstep);
            if (stima_ene<ene) {
                ene = stima_ene;
                mu = imu;
                sigma = isigma;
            }
            var << imu << " " << isigma << " " << stima_ene << endl;
            //cout << "mu :" << imu << endl;
            //cout << "sigma :" << isigma << endl;
            //cout << "energia :" << stima_ene << endl << endl;
            stima_ene = 0.;
        }
    }
    
    cout << endl << mu << endl << sigma << endl << endl;
    
    // cout << "Energy: " << ene/double(Nstep) << endl << endl;
    
    //===============================================================================
    //================================ Block Average ================================
    //===============================================================================
    
    /*ofstream Ene("energy.out");
    if (!Ene) cerr << "Non posso creare il file energy.out" << endl;
    
    ofstream Pos("position.out");
    if (!Pos) cerr << "Non posso creare il file position.out" << endl;
    
    for (int i=0; i<N; ++i) MTR->Step_Unif(); // equilibration

    int Nblocks = 100;
    int L = 5000;
    double ene=0., ene2=0.;
    for (int iblock=0; iblock<Nblocks; iblock++) {
        double stima_ene=0;
        MTR->Reset_Acception();
        for (int j=0; j<L; j++) {
            MTR->Step_Unif();
            x = MTR->Get_Pos();
            stima_ene += -0.5*Psi_T->Eval_sec(x)/Psi_T->Eval(x)+pow(x,4)-2.5*pow(x,2);
            Pos << x << " ";
        }
        double A = MTR->Get_Acception();
        if ((iblock+1)%10==0) cout << "Block number " << iblock+1 << endl << "Acceptance rate: " << (double)A/(double)L << endl << endl;
        ene += stima_ene/L;
        ene2 += pow(stima_ene/L,2);
        Ene << (iblock+1) << " " << ene/(iblock+1) << " " << err(ene,ene2,iblock+1) << endl;
    }
    
    Ene.close();
    Pos.close(); */
    
    rnd->SaveSeed();
    
    delete rnd;
       
    return 0;
}
