#include "funzioni.h"
#include <cmath>

double err (double med, double med2, int n) {
    if (n==0) return 0;
    else return sqrt((med2/(n) - pow(med/(n),2))/n);
}

double dist (const vector<double>& pos) { 
    double r=0.;
    for (int i=0; i<pos.size(); i++) r += pos[i]*pos[i];
    return r;
}

double max (double x, double y) {
    if (x>y) return x;
    else return y;
}

double min (double x, double y) {
    if (x>y) return y;
    else return x;
}

void print (const vector<double>& x) {
    cout << "Componenti del vettore: (" ;
    for (int i=0; i<x.size(); i++) {
        if (i+1 == x.size() ) cout << x[i];
        else cout << x[i] << ", ";
    }
    cout << ")" << endl << endl;
}
