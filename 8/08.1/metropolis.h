#ifndef __Metropolis__
#define __Metropolis__
#include "funzionebase.h"
#include "random.h"
#include "funzioni.h"

class Metropolis {

private:
    double m_step; // step of the uniform transition probability
    double m_sigma; // std dev of the gaussian transition probability
    double m_x;
    Random * m_rand;
    const FunzioneBase * m_pdf; // densità di probabilità da campionare
    int m_accept; // numero di volte che viene accettata la nuova configurazione

public:
    // constructors
    Metropolis(double step, double sigma, double x, const FunzioneBase* pdf, Random* rand);
    // destructor
    ~Metropolis() {;}
    // methods
    double Get_Pos() {return m_x;}
    void Set_Pos(double x) {m_x = x;}
    double Get_Pos() const {return m_step;}
    void Set_Step (double step) {m_step = step;}
    void Set_Sigma (double sigma) {m_sigma = sigma;}
    void Reset_Acception() {m_accept=0;}
    int Get_Acception() {return m_accept;}
    void Step_Unif();
    void Step_Gauss();
    
};

#endif // __Metropolis__
