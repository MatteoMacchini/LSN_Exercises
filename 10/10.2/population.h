#ifndef __Population__
#define __Population__

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "random.h"
#include "chromosome.h"

using namespace std;

class Population {

private:
    unsigned int m_n_chrom; // number of chromosomes
    vector<Chromosome> m_pop; // population
    double m_p; // convenient exponent for selection
    Random * m_rand;
    bool m_c; // se m_c == true sto simulando il cerchio
              // se m_c == falso sto simulando il quadrato

public:
    // constructors
    Population(Random * rand, unsigned int n_chrom, double p);
    // destructor
    ~Population() {;}
    
    // methods
    vector<Chromosome> Get_Pop() const {return m_pop;}
    unsigned int Get_N_Chrom() const {return m_n_chrom;}
    vector<int> Get_Best() const {
        vector<int> best = m_pop[0].Get_chrom();
        return best;
    }
    
    void Sort(); // ordina i cromosomi per costo decrescente
    void First_Pop_Square(unsigned int N, double l); // genera prima popolazione (quadrato)
    void New_Pop(); // genera nuova popolazione
    void Change_Chrom(vector<int> chrom, int site);
    
    double Best_Path_Length(); // costo del miglior cammino
    double Half_Best_Ave(); // costo medio della metà migliore della popolazione
    void Print_Best_Path(string filename); // stampa il miglior cammino
    void Print_on_File(string filename); // stampa popolazione attuale
    
    
};

#endif // __Population__

