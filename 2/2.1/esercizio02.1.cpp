#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "random.h"
#include "funzionebase.h"
#include "integral.h"

using namespace std;

double err (double med, double med2, int n) {
    if (n==1) return 0;
    else return sqrt((med2/(n) - pow(med/(n),2))/(n-1));
};
 
int main (int argc, char *argv[]){
    
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

    double a=0.;
    double b=1.;
    int Nblocks = 200; // numero di blocchi
    int N=10000; // numero di lanci in ogni blocco
    
    Coseno * mycos = new Coseno(M_PI/2.,M_PI/2.,0.);
    Integral * integrale = new Integral(a,b,mycos,rnd);
    
    ofstream inte("integral.out");
    if (!inte) cerr << "Non posso creare il file integral.out" << endl;
    
    double ave=0., av2=0., ave_IS=0., av2_IS =0.;
    
    for (int i=0; i<Nblocks; i++) {
        double I = integrale->Ave(N); // integrale con metodo della media
        double IS = integrale->Ave_IS(N); // importance sampling
        ave += I;
        av2 += pow(I,2);
        ave_IS += IS;
        av2_IS += pow(IS,2);
        inte << (i+1) << " " << ave/(i+1) << " " << err(ave, av2, (i+1)) << " " << ave_IS/(i+1) << " " << err(ave_IS, av2_IS, (i+1)) << endl;
    }
    
    inte.close();
    
    rnd->SaveSeed();
    
    return 0;
}
