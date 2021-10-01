#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "random.h"

using namespace std;
 
int main (int argc, char *argv[]){
    
    //===========================================================================

    Random rnd;
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
                rnd.SetRandom(seed,p1,p2);
            }
        }
        input.close();
    } else cerr << "PROBLEM: Unable to open seed.in" << endl;
    
    //===========================================================================

    int M = 10000;
    
    ofstream unif("unif.out");
    if (!unif) cerr << "Non posso creare il file unif.out" << endl;
    ofstream exp("exp.out");
    if (!exp) cerr << "Non posso creare il file exp.out" << endl;
    ofstream cauchy("cauchy.out");
    if (!cauchy) cerr << "Non posso creare il file cauchy.out" << endl;
    
    vector<int> N{1,2,10,100};
    
    for (int i=0; i<M; i++) {
        for (int j=0; j<4; j++) { // scorro sulle componenti del vettore N
            double sn_unif=0., sn_exp=0., sn_cauchy=0.;
            for (int s=0; s<N[j]; s++) { 
                sn_exp += rnd.Exp(1.);
                sn_unif += rnd.Rannyu();
                sn_cauchy += rnd.Cauchy(0.,1.);
            }
            unif << sn_unif/N[j] << " ";
            exp << sn_exp/N[j] << " ";
            cauchy << sn_cauchy/N[j] << " ";
        }
        unif << endl;
        exp << endl;
        cauchy << endl;
    }
    
    unif.close();
    exp.close();
    cauchy.close();
    
    rnd.SaveSeed();
    
    return 0;
}
