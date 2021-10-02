#ifndef __Metropolis__
#define __Metropolis__
#include "random.h"
#include "chromosome.h"

class Metropolis {

private:
    double m_beta; // inverse of temperature
    Chromosome m_cities;
    Chromosome m_best;
    Random * m_rand;
    // const FunzioneBase * m_pdf; // densità di probabilità da campionare
    double m_accept; // numero di volte che viene accettata la nuova configurazione

    
public:
    // constructors
    Metropolis(Random * rand);
    
    // destructor
    ~Metropolis() {;}
    
    // methods
    void Set_Beta (double beta) {m_beta = beta;}
    double Get_Beta () {return m_beta;}
    void Reset_Acception() {m_accept = 0.;}
    double Get_Acception() {return m_accept;}
    
    void Step(); // Step with Boltzmann distribution
    void Print_Best_Path(); // stampo su file il miglior percorso
    double Best_Cost() {return m_best.Cost();}
    
};

#endif // __Metropolis__
