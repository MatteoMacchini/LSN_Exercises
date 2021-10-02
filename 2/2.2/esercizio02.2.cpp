#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "random.h"

using namespace std;

double err (double med, double med2, int n) {
    if (n==0) return 0;
    else return sqrt((med2/(n) - pow(med/(n),2))/n);
};

double dist (const vector<double> & pos) {
    double r=0.;
    for (int i=0; i<pos.size(); i++) r += pos[i]*pos[i];
    return r;
};
 
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

    ofstream discr("RW_discr.out");
    if (!discr) cerr << "Non posso creare il file RW_discr.out" << endl;
        
    int M = 10000;
    int Nb = 100; // numero di blocchi
    int L = M/Nb; // numero di RW in ogni blocco
    int N = 101;
    double a=1.; // passo
    
    //===========================================================================
    //=============================== Discrete RW ===============================
    //===========================================================================
    
    vector<double> r_n(N,0);
    vector<double> r_n2(N,0);
    
    for (int j=0; j<Nb; j++) { 
        vector<double> R(N,0);
        for (int k=0; k<L; k++) {
            vector<double> pos(3,0);
            for (int i=0; i<N; i++) { // singolo RW completo
                R[i] += dist(pos);
                int step = a*((int)rnd->Rannyu(0.,2.)*2-1); // backward/forward step
                int di = (int)rnd->Rannyu(0.,3.); // direzione step
                pos[di] += step; // aggiorno posizione
            }
        }
        for (int t=0; t<N; t++) { // medie di blocco
            r_n[t] += R[t]/L;
            r_n2[t] += pow(R[t]/L,2);
        }
    }
        
    // no medie progressive, stampo solo media finale del blocco con incertezza
    for (int i=0; i<N; i++) {
        discr << i << " " << sqrt(r_n[i]/Nb) << " " << (err(r_n[i], r_n2[i], Nb))/(2*sqrt(r_n[i]/Nb)) << endl;
    }
    
    discr.close();
    
    //===========================================================================
    //=============================== Continuum RW ==============================
    //===========================================================================
    
    ofstream cont("RW_cont.out");
    if (!cont) cerr << "Non posso creare il file RW_cont.out" << endl;
    
    fill(r_n.begin(), r_n.end(), 0); // 
    fill(r_n2.begin(), r_n2.end(), 0);
    
    for (int j=0; j<Nb; j++) {
        vector<double> R(N,0);
        for (int k=0; k<L; k++) {
            vector<double> pos(3,0);
            for (int i=0; i<N; i++) { // singolo RW completo
                R[i] += dist(pos);
                double phi = rnd->Rannyu(0,2.*M_PI);
                double theta = rnd->Ranntheta();
                pos[0] += a*sin(theta)*cos(phi); // aggiorno posizione
                pos[1] += a*sin(theta)*sin(phi);
                pos[2] += a*cos(theta);
            }
        }
        for (int t=0; t<N; t++) { // medie di blocco
            r_n[t] += R[t]/L;
            r_n2[t] += pow(R[t]/L,2);
        }
    }
    
    // no medie progressive, stampo solo media finale del blocco con incertezza
    for (int i=0; i<N; i++) {
        cont << i << " " << sqrt(r_n[i]/Nb) << " " << (err(r_n[i], r_n2[i], Nb))/(2*sqrt(r_n[i]/Nb)) << endl;
    }
    
    cont.close();
    
    rnd->SaveSeed();
    
    return 0;
}
