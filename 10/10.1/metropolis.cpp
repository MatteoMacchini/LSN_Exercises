#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "metropolis.h"

using namespace std;

Metropolis :: Metropolis (Random * rand) {
    unsigned int N = 32;
    Chromosome cities(N, rand);
    cities.Cities();
    m_cities = cities;
    m_best = m_cities;
    m_rand = rand;
    m_accept = 0;
}

void Metropolis :: Step () {
    Chromosome next = m_cities;
    double A=0., r=0.;
    
    // mutation 1
    next.Swap();
    A = min(1., exp(-(next.Cost()-m_cities.Cost())*m_beta));
    r = m_rand->Rannyu();
    if (r<=A)  {
        m_cities = next; // accetto la nuova configurazione
        m_accept ++;
    }
    if (m_cities.Cost()<m_best.Cost()) m_best = m_cities;
    next = m_cities;
    
    // mutation 2
    next.Inversion();
    A = min(1., exp(-(next.Cost()-m_cities.Cost())*m_beta));
    r = m_rand->Rannyu();
    if (r<=A)  {
        m_cities = next; // accetto la nuova configurazione
        m_accept ++;
    }
    if (m_cities.Cost()<m_best.Cost()) m_best = m_cities;
    next = m_cities;
    
    // mutation 3
    next.Shift();
    A = min(1., exp(-(next.Cost()-m_cities.Cost())*m_beta));
    r = m_rand->Rannyu();
    if (r<=A)  {
        m_cities = next; // accetto la nuova configurazione
        m_accept ++;
    }
    if (m_cities.Cost()<m_best.Cost()) m_best = m_cities;
    next = m_cities;
    
    // mutation 4
    next.Cycle();
    A = min(1., exp(-(next.Cost()-m_cities.Cost())*m_beta));
    r = m_rand->Rannyu();
    if (r<=A)  {
        m_cities = next; // accetto la nuova configurazione
        m_accept ++;
    }
    if (m_cities.Cost()<m_best.Cost()) m_best = m_cities;
    next = m_cities;
    
    // mutation 5
    next.Swap_Sequence();
    A = min(1., exp(-(next.Cost()-m_cities.Cost())*m_beta));
    r = m_rand->Rannyu();
    if (r<=A)  {
        m_cities = next; // accetto la nuova configurazione
        m_accept ++;
    }
    if (m_cities.Cost()<m_best.Cost()) m_best = m_cities;
}

void Metropolis :: Print_Best_Path () {
    ofstream fout("final_path_square.out");
    if (!fout) cerr << "Non posso creare il file final_path_square.out" << endl;
    //ofstream fout("final_path_circle.out");
    //if (!fout) cerr << "Non posso creare il file final_path_circle.out" << endl;
    vector<int> best = m_best.Get_chrom();
    for (int i=0; i<best.size(); i++) fout << best[i] << endl;
    fout.close();
}
