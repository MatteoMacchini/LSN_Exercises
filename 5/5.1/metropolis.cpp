#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "metropolis.h"

using namespace std;

Metropolis :: Metropolis(double step, double sigma, vector<double> x, const FunzioneBase* pdf, Random * rand) {
    m_step = step;
    m_sigma = sigma;
    m_x = x;
    m_rand = rand;
    m_pdf = pdf;
    m_accept = 0;
}

void Metropolis :: Step_Unif () {
    vector<double> y(m_x.size(),0); // vettore di zeri della stessa dimensione di m_x
    for (int i=0; i<m_x.size(); i++) y[i] = m_rand->Rannyu(m_x[i]-m_step/2.,m_x[i]+m_step/2.);

    double A = min(1., m_pdf->Eval(y) / m_pdf->Eval(m_x));
    double r = m_rand->Rannyu();
    
    if (r<=A)  {
        m_x = y; // accetto la nuova configurazione
        m_accept ++;
    }
}

void Metropolis :: Step_Gauss () {
    vector<double> y(m_x.size(),0); // vettore di zeri della stessa dimensione di m_x
    for (int i=0; i<m_x.size(); i++) y[i] = m_rand->Gauss(m_x[i], m_sigma);

    double A = min(1., m_pdf->Eval(y) / m_pdf->Eval(m_x));
    double r = m_rand->Rannyu();
    
    if (r<=A)  {
        m_x = y; // accetto la nuova configurazione
        m_accept ++;
    }
}
