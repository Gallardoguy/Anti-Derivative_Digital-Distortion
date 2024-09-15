#pragma once

#ifndef PeakEQ_H
#define PeakEQ_H

class PeakEQ {
private:

    float b0, b1, b2, a0, a1, a2;
    float fs, f0, dbgain, bw;
    float A, alpha, w0;
    float x0, x1, x2;
    float y0, y1, y2;

    public:
        PeakEQ() = default;                
        ~PeakEQ() = default;

        void Init();
        
        float Process(float in);

        void setGain(float gain);

        void setParams(float f, float bw, float Q);
    };

#endif // PeakEQ_H