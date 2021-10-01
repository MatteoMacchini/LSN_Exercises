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
    int M=1000000; // numero totale di lanci
    int L=int(M/N); // numero di lanci in ogni blocco
    
    //===========================================================================
    //================================== Media ==================================
    //===========================================================================

    double ave = 0;
    double av2 = 0;
    ofstream med("media.out");
    if (!med) cerr << "PROBLEMA: non posso creare il file media.out" << endl;
    
    for (int i=0; i<N; i++) {
        double sum = 0;
        for (int j=0; j<L; j++) sum += rnd.Rannyu();
        ave += sum/L;
        av2 += pow(sum/L,2);
        double err_prog = err(ave,av2,i+1);
        med << i+1 << " " << ave/(i+1) << " " << err_prog << endl;
    }
    
    med.close();
    
    //===========================================================================
    //================================ Varianza =================================
    //===========================================================================

    ave = 0;
    av2 = 0;
    ofstream var("varianza.out");
    if (!var) cerr << "PROBLEMA: non posso creare il file varianza.out" << endl;
    
    for (int i=0; i<N; i++) {
        double sum = 0;
        for (int j=0; j<L; j++) sum += pow((rnd.Rannyu()-0.5),2);
        ave += sum/L;
        av2 += pow(sum/L,2);
        double err_prog = err(ave,av2,i+1);
        var << i+1 << " " << ave/(i+1) << " " << err_prog << endl;
    }
    
    var.close();
    
    //===========================================================================
    //=============================== Chi Quadro ================================
    //===========================================================================

    M = 100; 
    int n = 10000;
    ofstream chi("chi_quad.out");
    if (!chi) cerr << "PROBLEMA: non posso creare il file chi_quad.out" << endl;

    
    for (int i=0; i<M; i++) {
        vector<int> n_i(M,0);
        double sum = 0;
        for (int j=0; j<n; j++) { // conto quante volte i numeri vengono estratti in un dato sottointervallo
            int r = int(rnd.Rannyu()*M);
            n_i[r] ++;
        }
        for (int k=0; k<M; k++) sum += (pow((n_i[k]-100),2))/(100);
        chi << i+1 << " " << sum << endl;
    }
    
    chi.close();
    
    //===========================================================================

    rnd.SaveSeed();
    
    return 0;
}
