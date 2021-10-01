#include <iostream>
#include <fstream>
#include <string>
#include "random.h"
#include "funzioni.h"
#include "brownianmotion.h"


using namespace std;
 
int main (int argc, char *argv[]) {
    
    //===========================================================================

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
    
    //===========================================================================

    double S0 = 100.;
    double T = 1.;
    double K = 100.;
    double r = 0.1;
    double sigma = 0.25;
        
    int M = 40000;
    int N = 400; // numero di blocchi
    int L = M/N; // estrazioni prezzi call/put in ogni blocco
    
    BrownianMotion gbm(r, sigma, rnd);

    //===========================================================================
    //============================ Direct asset price ===========================
    //===========================================================================
    
    ofstream c_dir("direct_call.out");
    if (!c_dir) cerr << "Non posso creare il file direct_call.out" << endl;
    
    ofstream p_dir("direct_put.out");
    if (!p_dir) cerr << "Non posso creare il file direct_put.out" << endl;
    
    double ave_c = 0., av2_c = 0., ave_p =0., av2_p = 0;
    
    for (int i=0; i<N; i++) {
        double call=0., put=0.;
        for (int j=0; j<L; j++) {
            call += exp(-r*T)*max(0.,gbm.GBM(S0,T)-K); // call
            put += exp(-r*T)*max(0.,K-gbm.GBM(S0,T)); // put
        }
        ave_c += call/L;
        av2_c += pow(call/L,2);
        ave_p += put/L;
        av2_p += pow(put/L,2);
        c_dir << i+1 << " " << ave_c/(i+1) << " " << err(ave_c,av2_c,i+1) << endl;
        p_dir << i+1 << " " << ave_p/(i+1) << " " << err(ave_p,av2_p,i+1) << endl;
    }
    
    c_dir.close();
    p_dir.close();
    
    //===========================================================================
    //=========================== Discrete asset price ==========================
    //===========================================================================
    
    ofstream c_dis("discrete_call.out");
    if (!c_dis) cerr << "Non posso creare il file discrete_call.out" << endl;

    
    ofstream p_dis("discrete_put.out");
    if (!p_dis) cerr << "Non posso creare il file discrete_put.out" << endl;
    
    ave_c = 0., av2_c = 0., ave_p =0., av2_p = 0;
    
    for (int i=0; i<N; i++) {
        double call=0., put=0.;
        for (int j=0; j<L; j++) {
            double St=S0;
            for (int k=1; k<101; k++) {
                double t = k*T/100.;
                double eval = gbm.GBM(St,t,t-0.01);
                St = eval;
                
            }
            call += exp(-r*T)*max(0.,gbm.GBM(S0,T)-K); // call
            put += exp(-r*T)*max(0.,K-gbm.GBM(S0,T)); // put
        }
        ave_c += call/L;
        av2_c += pow(call/L,2);
        ave_p += put/L;
        av2_p += pow(put/L,2);
        c_dis << i+1 << " " << ave_c/(i+1) << " " << err(ave_c,av2_c,i+1) << endl;
        p_dis << i+1 << " " << ave_p/(i+1) << " " << err(ave_p,av2_p,i+1) << endl;
    }
    
    c_dis.close();
    p_dis.close();
    
    rnd->SaveSeed();
    
    return 0;
}
