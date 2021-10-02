#ifndef __Integral__
#define __Integral__
#include "funzionebase.h"
#include "random.h"

class Integral {

 public:
    
    Integral (double a, double b, const FunzioneBase* f, Random* rand);
    double Ave (unsigned int punti);
    double Ave_IS (unsigned int punti);
    double Exact (unsigned int punti);
    
 private:
    
    double m_a, m_b;
    // double m_sum;
    // double m_h;
    int m_sign;
    double m_integral;
    const FunzioneBase* m_f;
    Random* m_rand;
    
};

#endif 

