#ifndef __BrownianMotion__
#define __BrownianMotion__
#include "random.h"

class BrownianMotion {

private:
    double m_drift, m_vol;
    Random* m_rand;

protected:

public:
    // constructors
    BrownianMotion(Random* rand);
    BrownianMotion(double drift, double vol, Random* rand);
    
    // destructor
    ~BrownianMotion() {;};
    
    // methods
    double GetDrift() const {return m_drift;}
    double GetVol() const {return m_vol;}
    void SetDrift(double drift) {m_drift = drift;}
    void SetVol(double vol) {m_vol = vol;}

    double GBM (double S0, double t);
    double GBM (double S0, double t, double s);
    
};

#endif // __BrownianMotion__

