#include "integral.h"
#include <algorithm>

using namespace std;

Integral :: Integral(double a, double b, const FunzioneBase* f, Random* rand) {
    m_f=f;
    m_rand=rand;
    m_a=min(a,b);
    m_b=max(a,b);
    if (a>b) m_sign = -1;
    else m_sign =1;
}

double Integral :: Ave (unsigned int punti) {
    m_integral = 0.;
    for (unsigned int i=0; i<punti; i++) {
        m_integral += m_f->Eval(m_rand->Rannyu(m_a, m_b));
    }
    m_integral = (double)m_sign*(m_b-m_a)*m_integral/(double)punti;
    return m_integral;
}

double Integral :: Ave_IS (unsigned int punti) {
    m_integral = 0.;
    for (unsigned int i=0; i<punti; i++) {
        double s = m_rand->Straight();
        m_integral += (m_f->Eval(s))/(-2*s+2);
    }
    m_integral = (double)m_sign*(m_b-m_a)*m_integral/(double)punti;
    return m_integral;
}
