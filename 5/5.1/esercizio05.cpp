#include <iostream>
#include <fstream>
#include <string>
#include "random.h"
#include "funzioni.h"
#include "metropolis.h"
#include "funzionebase.h"


using namespace std;
 
int main (int argc, char *argv[]){
    
    // =======================================================================

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
    
    // =======================================================================
    
    cout << endl << endl << "METROPOLIS ALGORITHM" << endl << endl;

    // Setting the step of the uniform transition probability T(x|y)
    double step = 2.42;
    
    double sigma = 0.75;
    
    // Setting initial position
    vector<double> x1;
    x1.push_back(70.);
    x1.push_back(70.);
    x1.push_back(70.);
    
    vector<double> x2;
    x2.push_back(0.9);
    x2.push_back(0.9);
    x2.push_back(0.9);
    
    // =======================================================================
    // ============================= Psi (1,0,0) =============================
    // =======================================================================

    Psi100 * Psi_100 = new Psi100();
    Metropolis * MTR = new Metropolis(step, sigma, x1, Psi_100, rnd);
    
    cout << "HYDROGEN ATOM - WAVE FUNCTION (1,0,0)" << endl;
    
    // =================== Uniform transition probability ====================
    
    cout << "-------------------------------------------------" << endl;
    cout << "Uniform transition probability: step = " << step << endl;
    
    // ============================ Equilibration ============================

    int N = 200000;

    ofstream uf_100("eq_100_unif_far.out");
    if (!uf_100) cerr << "Non posso creare il file eq_100_unif_far.out" << endl;
    uf_100 << 0 << " " << sqrt(dist(x1)) << endl;
    
    for (int i=0; i<N; ++i) {
        MTR->Step_Unif();
        uf_100 << i+1 << " " << MTR->Get_R() << endl;
    }
        
    uf_100.close();
    
    MTR->Set_Pos(x2);
    
    ofstream u_100("eq_100_unif.out");
    if (!u_100) cerr << "Non posso creare il file eq_100_unif.out" << endl;
    u_100 << 0 << " " << sqrt(dist(x2)) << endl;
    
    for (int i=0; i<N; ++i) {
        MTR->Step_Unif();
        u_100 << i+1 << " " << MTR->Get_R() << endl;
    }
        
    u_100.close();
    
    cout << "System equilibrated ... Starting simulation ..." << endl << endl;
    
    // ============================= Simulation ==============================

    int M = 300000;
    int Nblocks = 300;
    int L = M/Nblocks;
    
    ofstream du_100("dist_100_unif.out");
    if (!du_100) cerr << "Non posso creare il file dist_100_unif.out" << endl;

    ofstream posu_100("pos_100_unif.out");
    if (!posu_100) cerr << "Non posso creare il file pos_100_unif.out" << endl;
    
    double ave=0., av2=0.;
    for (int i=1; i<=Nblocks; i++) {
        double r=0., A=0.;
        MTR->Reset_Acception();
        for (int j=0; j<L; j++) {
            MTR->Step_Unif();
            r += MTR->Get_R();
            if(j%10==0) {
                vector<double> pos = MTR->Get_Pos();
                posu_100 << pos[0] << " " << pos[1] << " " << pos[2] << endl;
            }
        }
        A = MTR->Get_Acception();
        if (i%25==0) cout << "Block number " << i << ", acceptance rate = " << A/L << endl;

        ave += r/L;
        av2 += pow(r/L,2);
        du_100 << i << " " << ave/i << " " << err(ave,av2,i) << endl;
    }
    du_100.close();
    posu_100.close();
    
    cout << "-------------------------------------------------" << endl;
    // =================== Gaussian transition probability ===================
    
    cout << "Gaussian transition probability: sigma = " << sigma << endl;
    
    // ============================ Equilibration ============================

    MTR->Set_Pos(x1);
    
    ofstream gf_100("eq_100_gaus_far.out");
    if (!gf_100) cerr << "Non posso creare il file eq_100_gaus_far.out" << endl;
    gf_100 << 0 << " " << sqrt(dist(x1)) << endl;

    for (int i=0; i<N; ++i) {
        MTR->Step_Gauss();
        gf_100 << i+1 << " " << MTR->Get_R() << endl;
    }
    
    gf_100.close();
    
    MTR->Set_Pos(x2);
    
    ofstream g_100("eq_100_gaus.out");
    if (!g_100) cerr << "Non posso creare il file eq_100_gaus.out" << endl;
    g_100 << 0 << " " << sqrt(dist(x2)) << endl;
    
    for (int i=0; i<N; ++i) {
        MTR->Step_Gauss();
        g_100 << i+1 << " " << MTR->Get_R() << endl;
    }
        
    g_100.close();
    
    cout << "System equilibrated ... Starting simulation ..." << endl << endl;

    // ============================= Simulation ==============================
        
    ofstream dg_100("dist_100_gaus.out");
    if (!dg_100) cerr << "Non posso creare il file dist_100_gaus.out" << endl;
    
    ofstream posg_100("pos_100_gaus.out");
    if (!posg_100) cerr << "Non posso creare il file pos_100_gaus.out" << endl;
    
    ave = 0.; av2 = 0.;
    for (int i=1; i<=Nblocks; i++) {
        double r=0., A=0.;
        MTR->Reset_Acception();
        for (int j=0; j<L; j++) {
            MTR->Step_Gauss();
            r += MTR->Get_R();
            if(j%10==0) {
                vector<double> pos = MTR->Get_Pos();
                posg_100 << pos[0] << " " << pos[1] << " " << pos[2] << endl;
            }
        }
        A = MTR->Get_Acception();
        if (i%25==0) cout << "Block number " << i << ", acceptance rate = " << A/L << endl;
    
        ave += r/L;
        av2 += pow(r/L,2);
        dg_100 << i << " " << ave/i << " " << err(ave,av2,i) << endl;
    }
    dg_100.close();
    posg_100.close();
        
    delete MTR;
    
    cout << "-------------------------------------------------" << endl;
    cout << "-------------------------------------------------" << endl << endl;
    
    // =======================================================================
    // ============================= Psi (2,1,0) =============================
    // =======================================================================
    
    // Setting initial position
    vector<double> y1;
    y1.push_back(90.);
    y1.push_back(90.);
    y1.push_back(90.);
    
    vector<double> y2;
    y2.push_back(2.8);
    y2.push_back(2.8);
    y2.push_back(2.8);
    
    cout << "HYDROGEN ATOM - WAVE FUNCTION (2,1,0)" << endl;

    step = 5.8;
    sigma = 1.9;
    
    Psi210 * Psi_210 = new Psi210();
    MTR = new Metropolis(step, sigma, y1, Psi_210, rnd);
    
    // =================== Uniform transition probability ====================
    
    cout << "-------------------------------------------------" << endl;
    cout << "Uniform transition probability: step = " << step << endl;
    
    // ============================ Equilibration ============================

    ofstream uf_210("eq_210_unif_far.out");
    if (!uf_210) cerr << "Non posso creare il file eq_210_unif_far.out" << endl;
    uf_210 << 0 << " " << sqrt(dist(y1)) << endl;

    for (int i=0; i<N; ++i) {
        MTR->Step_Unif();
        uf_210 << i+1 << " " << MTR->Get_R() << endl;
    }
        
    uf_210.close();
                              
    MTR->Set_Pos(y2);
    
    ofstream u_210("eq_210_unif.out");
    if (!u_210) cerr << "Non posso creare il file eq_210_unif.out" << endl;
    u_210 << 0 << " " << sqrt(dist(y2)) << endl;

    for (int i=0; i<N; ++i) {
        MTR->Step_Unif();
        u_210 << i+1 << " " << MTR->Get_R() << endl;
    }
                                  
    u_210.close();
    
    cout << "System equilibrated ... Starting simulation ..." << endl << endl;
    
    // ============================= Simulation ==============================
    
    ofstream du_210("dist_210_unif.out");
    if (!du_210) cerr << "Non posso creare il file dist_210_unif.out" << endl;

    ofstream posu_210("pos_210_unif.out");
    if (!posu_210) cerr << "Non posso creare il file pos_210_unif.out" << endl;
    
   ave=0., av2=0.;
    for (int i=1; i<=Nblocks; i++) {
        double r=0., A=0.;
        MTR->Reset_Acception();
        for (int j=0; j<L; j++) {
            MTR->Step_Unif();
            r += MTR->Get_R();
            if(j%10==0) {
                vector<double> pos = MTR->Get_Pos();
                posu_210 << pos[0] << " " << pos[1] << " " << pos[2] << endl;
            }
        }
        A = MTR->Get_Acception();
        if (i%25==0) cout << "Block number " << i << ", acceptance rate = " << A/L << endl;

        ave += r/L;
        av2 += pow(r/L,2);
        du_210 << i << " " << ave/i << " " << err(ave,av2,i) << endl;
    }
    du_210.close();
    posu_210.close();
    
    cout << "-------------------------------------------------" << endl;
    // =================== Gaussian transition probability ===================
    
    cout << "Gaussian transition probability: sigma = " << sigma << endl;
    
    // ============================ Equilibration ============================

    MTR->Set_Pos(y1);
    
    ofstream gf_210("eq_210_gaus_far.out");
    if (!gf_210) cerr << "Non posso creare il file eq_210_gaus_far.out" << endl;
    gf_210 << 0 << " " << sqrt(dist(y1)) << endl;

    for (int i=0; i<N; ++i) {
        MTR->Step_Gauss();
        gf_210 << i+1 << " " << MTR->Get_R() << endl;
    }
    
    gf_210.close();
                              
    MTR->Set_Pos(y2);
    
    ofstream g_210("eq_210_gaus.out");
    if (!g_210) cerr << "Non posso creare il file eq_210_gaus.out" << endl;
    g_210 << 0 << " " << sqrt(dist(y2)) << endl;

    for (int i=0; i<N; ++i) {
        MTR->Step_Gauss();
        g_210 << i+1 << " " << MTR->Get_R() << endl;
    }
                                                            
    g_210.close();
                              
    cout << "System equilibrated ... Starting simulation ..." << endl << endl;

    // ============================= Simulation ==============================
        
    ofstream dg_210("dist_210_gaus.out");
    if (!dg_210) cerr << "Non posso creare il file dist_210_gaus.out" << endl;
    
    ofstream posg_210("pos_210_gaus.out");
    if (!posg_210) cerr << "Non posso creare il file pos_210_gaus.out" << endl;
    
    ave = 0.; av2 = 0.;
    for (int i=1; i<=Nblocks; i++) {
        double r=0., A=0.;
        MTR->Reset_Acception();
        for (int j=0; j<L; j++) {
            MTR->Step_Gauss();
            r += MTR->Get_R();
            if(j%10==0) {
                vector<double> pos = MTR->Get_Pos();
                posg_210 << pos[0] << " " << pos[1] << " " << pos[2] << endl;
            }
        }
        A = MTR->Get_Acception();
        if (i%25==0) cout << "Block number " << i << ", acceptance rate = " << A/L << endl;
    
        ave += r/L;
        av2 += pow(r/L,2);
        dg_210 << i << " " << ave/i << " " << err(ave,av2,i) << endl;
    }
    
    dg_210.close();
    posg_210.close();
        
    delete MTR;
    
    cout << "-------------------------------------------------" << endl;
    cout << "-------------------------------------------------" << endl << endl;
    
    rnd->SaveSeed();
    
    delete rnd;
   
    return 0;
}
