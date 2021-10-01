#ifndef __FunzioneBase__
#define __FunzioneBase__

#include <cmath>
#include <iostream>
#include <cstdlib>


using namespace std;

class FunzioneBase {

 public:
    virtual double Eval (double x) const=0;
};


class Seno: public FunzioneBase {
public:

    Seno();
    Seno(double a, double b, double c);
    
    ~Seno() {;};
    
    virtual double Eval(double x) const {return m_a*sin(m_b*x)+m_c;}
    
    void SetA(double a) {m_a=a;}
    double GetA() const {return m_a;}
    void SetB(double b) {m_b=b;}
    double GetB() const {return m_b;}
    void SetC(double c) {m_c=c;}
    double GetC() const {return m_c;}
    
    
private:
    double m_a, m_b, m_c;
};

class Coseno: public FunzioneBase {
public:

    Coseno(); //costruttore1
    Coseno(double a, double b, double c); //costruttore2
    
    ~Coseno() {;};
    
    virtual double Eval(double x) const {return m_a*cos(m_b*x)+m_c;}
    
    void SetA(double a) {m_a=a;}
    double GetA() const {return m_a;}
    void SetB(double b) {m_b=b;}
    double GetB() const {return m_b;}
    void SetC(double c) {m_c=c;}
    double GetC() const {return m_c;}
    
    
private:
    double m_a, m_b, m_c;
};

#endif // __Random__

