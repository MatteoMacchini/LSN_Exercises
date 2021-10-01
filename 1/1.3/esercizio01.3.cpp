#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "random.h"

using namespace std;

double err (double med, double med2, int n) {
    if (n==1) return 0;
    else return sqrt((med2/(n) - pow(med/(n),2))/(n-1));
};
 
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

    int N=200; // numero di blocchi
    int L=10000; // numero di lanci in ogni blocco
    double d=2.; // distanza tra le linee
    double l=1.75; // lunghezza ago

    ofstream pigr("pi.out");
    if (!pigr) cerr << "Non posso creare il file media.out" << endl;
    
    double ave=0;
    double av2=0;
        
    for (int i=0; i<N; i++) { 
        double pi=0;
        int Nh=0;
        for (int j=0; j<L; j++) {
            double x = rnd.Rannyu(0.,d); // estraggo centro
            double theta = rnd.Ranntheta(); // estraggo angolo
            if ((x+l*0.5*sin(theta))>=d or (x-l*0.5*sin(theta))<=0) Nh ++;
        }
        pi=(2.*l*double(L))/(d*double(Nh)); // 1 blocco = 1 stima di pigreco
        ave += pi;
        av2 += pow(pi,2);
        double err_prog = err(ave,av2,i+1);
        pigr << i+1 << " " << ave/(i+1) << " " << err_prog << endl;
    }

    pigr.close();
    
    rnd.SaveSeed();
    
    return 0;
}
