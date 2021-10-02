#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "brownianmotion.h"

using namespace std;

BrownianMotion :: BrownianMotion (Random* rand) {
    m_drift = 0.;
    m_vol = 1.;
    m_rand = rand;
}

BrownianMotion :: BrownianMotion (double drift, double vol, Random* rand) {
    m_drift = drift;
    m_vol = vol;
    m_rand = rand;
}

double BrownianMotion :: GBM (double S0, double t) {
    return S0*exp(m_rand->Gauss((m_drift-m_vol*m_vol/2.)*t, m_vol*sqrt(t)));
}

double BrownianMotion :: GBM (double Ss, double t, double s) {
    return Ss*exp(m_rand->Gauss((m_drift-m_vol*m_vol/2.)*(t-s), m_vol*sqrt(t-s)));
}

