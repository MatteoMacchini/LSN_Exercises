#ifndef __FunzioneBase__
#define __FunzioneBase__
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "funzioni.h"

using namespace std;

class FunzioneBase {

 public:
    virtual double Eval (vector<double> x) const=0;
};

class Psi100: public FunzioneBase {
public:
    //Psi100() {;};
    ~Psi100() {;};
    
    virtual double Eval(vector<double> x) const {return exp(-2*sqrt(dist(x)))/M_PI;}
};

class Psi210: public FunzioneBase {
public:
    //Psi210() {;};
    ~Psi210() {;};
    
    virtual double Eval(std::vector<double> x) const { return exp(-sqrt(dist(x)))*pow(x[2],2)/(32.*M_PI);}
};

#endif //__FunzioneBase__
