#ifndef __FunzioneBase__
#define __FunzioneBase__

#include <cmath>
#include <iostream>
#include <cstdlib>
// #include <vector>
#include "funzioni.h"


using namespace std;

class FunzioneBase {

 public:
    virtual double Eval (double x) const=0;
    virtual double Eval_pdf (double x) const=0;
    virtual double Eval_sec (double x) const=0;
};

class Psi_Trial: public FunzioneBase {
    
private:
    double m_mu, m_sigma;
    
public:
    // constructor
    Psi_Trial(double mu, double sigma);
    // destructor
    ~Psi_Trial() {;}
    
    // methods
    virtual double Eval (double x) const {return exp(-pow(x-m_mu,2)/(2*m_sigma*m_sigma)) + exp(-pow(x+m_mu,2)/(2*m_sigma*m_sigma));}
    virtual double Eval_pdf (double x) const {return pow(Eval(x),2);}
    virtual double Eval_sec (double x) const {return pow(x-m_mu,2)/pow(m_sigma,4)*exp(-pow(x-m_mu,2)/(2*m_sigma*m_sigma)) + pow(x+m_mu,2)/pow(m_sigma,4)*exp(-pow(x+m_mu,2)/(2*m_sigma*m_sigma)) - Eval(x)/pow(m_sigma,2);}
    
    double Get_Mu() {return m_mu;}
    void Set_Mu(double mu) {m_mu = mu;}
    double Get_Sigma()  {return m_sigma;}
    void Set_Sigma(double sigma) {m_sigma = sigma;}
    
};

#endif // __FunzioneBase__

