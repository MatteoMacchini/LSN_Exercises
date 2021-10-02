#include <string>
#include "random.h"
#include "chromosome.h"
#include "metropolis.h"

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

    
    cout << endl << "TRAVELING SALESMAN PROBLEM - Simulated Annealing"  << endl;
    
    //cout << endl << "32 Cities on a circumference of radius R = 1" << endl;
    cout << "32 Cities inside a square of size L = 1" << endl << endl;
    
    Metropolis * SA = new Metropolis(rnd);
    
    double beta;
    int M = 1000;
    
    ofstream fout("length_temp_square.out");
    if (!fout) cerr << "Non posso creare il file length_temp_square.out" << endl;
    
    //ofstream fout("length_temp_circle.out");
    //if (!fout) cerr << "Non posso creare il file length_temp_circle.out" << endl;
    
    //for (int t=0; t<30; t++) { // circle
    for (int t=0; t<50; t++) { // square
        SA->Reset_Acception();
        beta = 1. + (double)t;
        double T = 1/beta;
        SA->Set_Beta(beta);
        for (int j=0; j<M; j++) SA->Step();
        cout << "T = " << T << endl;
        cout << "Acceptance rate: " << (double)SA->Get_Acception()/(5.*(double)M) << endl << endl;
        fout << beta << " " << SA->Best_Cost() << endl;
        // cout << T << " " <<  t << endl;
    }
    
    fout.close();
    
    SA->Print_Best_Path();
    
    rnd->SaveSeed();
    delete rnd;
    
    return 0;
    
}
