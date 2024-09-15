#include "PeakEQ.h"

#define PI_F 3.1415927410125732421875f

void PeakEQ::Init(){
    bw = 100;
    w0 = 2 * PI_F * 1100 / 96000;
    alpha = sin(w0) / (2 * 0.707);

    
    x0 = 0;
    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;
}

float PeakEQ::Process(float in){
    x0 = in;
    y0 = (b0/a0) * x0 + (b1/a0) * x1 + (b2/a0) * x2 - (a1/a0) * y1 - (a2/a0) * y2;

    x2 = x1;
    x1 = x0;
    y2 = y1;
    y1 = y0;

    return y0;
}

void PeakEQ::setGain(float gain){
    A = pow(10, gain/40);

    b0 = 1 + alpha * A;
    b1 = -2 * cos(w0);
    b2 = 1 - alpha * A;
    a0 = 1 + alpha / A;
    a1 = -2 * cos(w0);
    a2 = 1 - alpha / A;
}

void PeakEQ::setParams(float f, float bw, float Q){
    bw = bw;
    w0 = 2 * PI_F * f / 96000;
    alpha = sin(w0) / (2 * Q);
}