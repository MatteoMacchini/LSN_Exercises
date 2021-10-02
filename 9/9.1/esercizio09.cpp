#include <string>
#include "random.h"
#include "chromosome.h"
#include "population.h"

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

    
    cout << endl << "TRAVELING SALESMAN PROBLEM - Genetic Algorithm"  << endl;
    
    unsigned int N = 32;
    double r = 1.;
    double l = 1.;
    double p = 2;
    unsigned int n_chrom = 100;
        
    //=====================================================
    //======================= Circle ======================
    //=====================================================
    
    cout << endl << "1) 32 Cities on a circumference of radius R = " << r << endl;
    
    Population C(rnd, n_chrom, p);

    ofstream Best_C("bp_length_circle.out");
    ofstream HB_C("half_length_circle.out");
    
    C.First_Pop_Circle(N,r);
    int M_c = 1000;
    for (int i=0; i<M_c; i++) {
        if ((i+1)%100==0) cout << "   Popolazione " << i+1 << "/" << M_c << " creata" << endl;
        C.New_Pop();
        Best_C << i+1 << " " << C.Best_Path_Length() << endl;
        HB_C << C.Half_Best_Ave() << endl;
    }
    
    Best_C.close();
    HB_C.close();
    
    C.Print_on_File();
    C.Print_Best_Path();
    
    //=====================================================
    //======================= Square ======================
    //=====================================================
    
    /*cout << endl << "2) 32 Cities inside a square of side L = " << l << endl;
    
    Population S(rnd, n_chrom, p);
    
    ofstream Best_S("bp_length_square.out");
    ofstream HB_S("half_length_square.out");
    
    S.First_Pop_Square(N,l);
    int M_s = 2000;
    for (int i=0; i<M_s; i++) {
        if ((i+1)%200==0) cout << "   Popolazione " << i+1 << "/" << M_s << " creata" << endl;
        S.New_Pop();
        Best_S << i+1 << " " << S.Best_Path_Length() << endl;
        HB_S << S.Half_Best_Ave() << endl;
    }
     
    Best_S.close();
    HB_S.close();
    
    S.Print_on_File();
    S.Print_Best_Path(); */
    
    rnd->SaveSeed();
    delete rnd;
    
    return 0;
    
}
