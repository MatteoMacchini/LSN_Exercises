#ifndef __Chromosome__
#define __Chromosome__

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "random.h"

using namespace std;

class Chromosome {

private:
    unsigned int m_N; // number of cities
    vector<int> m_chrom; // chromosome
    vector<vector<double>> m_dist; // matrice che contiene le distanze tra le città
    Random * m_rand;

public:
    // constructors
    Chromosome() {;}
    Chromosome(unsigned int N, Random* rand);
    // destructor
    ~Chromosome() {;}
    
    // methods
    vector<int> Get_chrom() const {return m_chrom;}
    void Set_chrom(vector<int> chrom) {m_chrom=chrom;}
    unsigned int Get_N() {return m_N;}
    void Set_N(unsigned int N) {m_N = N;}
    
    void Cities(); // leggo città dal file
    void Check(); // check function
    double Cost(); // chromosome cost function
    
    // Mutations
    void Swap(); // swap two cities
    void Inversion(); // inversion of contiguous cities
    void Shift(); // shift of +n positions for m contiguous cities
    void Cycle(); // cyclic permutation
    void Swap_Sequence(); // swap of two sequences of cities

};

#endif // __Chromosome__

