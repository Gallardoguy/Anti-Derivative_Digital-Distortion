#include "TSTone.h"

#define PI 3.14159265358979f

void TSTone::Init(){
    wc = 0;
    T = 1/96000.0f;
    wd = 0;
    b0 = 0;
    b1 = 0;
    b2 = 0;
    a1 = 0;
    a2 = 0;
    fc = 6000;
    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;
}

void TSTone::setFreq(float freq) {
    fc = freq;
    wc = 2*PI*fc;
    wd = 2*96000.0*tan(wc*T/2);
    float wd2 = wd * wd;
    float T2 = 2/T;

    A = wd2 + sqrt(2) * wd * T2 + (T2 * T2);
    b0 = wd2 / A;
    b1 = 2*b0;
    b2 = b0;
    a1 = 2 * (wd2 - (T2*T2))/A;
    a2 = (wd2 - sqrt(2) * wd * T2 + (T2*T2)) / A;
}


float TSTone::Process(float in){
    float out;

    out = b0 * in + b1*x1 + b2*x2 - a1*y1 - a2*y2;

    y2 = y1;
    y1 = out;
    x2 = x1;
    x1 = in;
    return out;

}