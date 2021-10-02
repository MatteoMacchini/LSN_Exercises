#ifndef __Integral__
#define __Integral__
#include "funzionebase.h"
#include "random.h"

class Integral {

 public:
    
    Integral (double a, double b, const FunzioneBase* f, Random* rand);
    
    ~Integral() {;};
    
    double Ave (unsigned int punti);
    double Ave_IS (unsigned int punti);
    
 private:
    
    double m_a, m_b;
    int m_sign;
    double m_integral;
    const FunzioneBase* m_f;
    Random* m_rand;
    
};

#endif 

