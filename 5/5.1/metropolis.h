#ifndef __Metropolis__
#define __Metropolis__
#include "funzionebase.h"
#include "random.h"
#include "funzioni.h"

class Metropolis {

private:
    double m_step; // step of the uniform transition probability
    double m_sigma; // std dev of the gaussian transition probability
    vector<double> m_x; // actual position of M(RT)^2 algorithm
    Random * m_rand;
    const FunzioneBase * m_pdf; // densità di probabilità da campionare
    int m_accept; // numero di volte che viene accettata la nuova configurazione

    
public:
    // constructors
    Metropolis(double step, double sigma, vector<double> x, const FunzioneBase* pdf, Random* rand);
    
    // destructor
    ~Metropolis() {;}
    
    // methods
    std::vector<double> Get_Pos() {return m_x;}
    void Set_Pos(vector<double> x) {m_x = x;}
    double Get_Pos() const {return m_step;}
    void Set_Step (double step) {m_step = step;}
    void Set_Sigma (double sigma) {m_sigma = sigma;}
    void Reset_Acception() {m_accept = 0;}
    int Get_Acception() {return m_accept;}
    double Get_R() {return sqrt(dist(m_x));}
    
    void Step_Unif(); // Metropolis step with uniform transition probability
    void Step_Gauss(); // Metropolis step with gaussian transition probability
    
};

#endif // __Metropolis__
