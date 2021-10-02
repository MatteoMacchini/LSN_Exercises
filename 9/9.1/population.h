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
    
    void Sort(); // ordina i cromosomi per costo decrescente
    void First_Pop_Circle(unsigned int N, double r); // genera prima popolazione (quadrato)
    void First_Pop_Square(unsigned int N, double r); // genera prima popolazione (cerchio)
    void New_Pop(); // genera nuova popolazione
    
    double Best_Path_Length(); // costo del miglior cammino
    double Half_Best_Ave(); // costo medio della metà migliore della popolazione
    void Print_Best_Path(); // stampa il miglior cammino
    void Print_on_File(); // stampa popolazione finale
    
    
};

#endif // __Population__

