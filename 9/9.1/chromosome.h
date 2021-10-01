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
    double m_r, m_l; // circumference radius, lato quadrato
    vector<int> m_chrom; // chromosome
    vector<vector<double>> m_dist; // matrice che contiene le distanze tra le città
    Random * m_rand;

public:
    // constructors
    Chromosome(unsigned int N, Random* rand);
    // destructor
    ~Chromosome() {;}
    
    // methods
    vector<int> Get_chrom() const {return m_chrom;}
    void Set_chrom(vector<int> chrom) {m_chrom=chrom;}
    unsigned int Get_N() {return m_N;}
    void Set_N(unsigned int N) {m_N = N;}
    double Get_r() const {return m_r;}
    void Set_r (double r) {m_r = r;}
    double Get_l() const {return m_l;}
    void Set_l (double l) {m_l = l;}
    
    void Circle(); // genera città su una circonferenza
    void Square(); // genera città dentro un quadrato
    void Check(); // check function
    double Cost(); // chromosome cost function
    
    void Gen_Rand(); // Fisher–Yates shuffle: generates random chromosome (permutazioni casuali)
    
    // Mutations
    void Swap(); // swap two cities
    void Inversion(); // inversion of contiguous cities
    void Shift(); // shift of +n positions for m contiguous cities
    void Cycle(); // cyclic permutation
    void Swap_Sequence(); // swap of two sequences of cities

};

#endif // __Chromosome__

