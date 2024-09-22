#pragma once

#ifndef TSTone_H
#define TSTone_H

class TSTone {
private:

    float wc, T, wd;
    float A, b0, b1, b2, a1, a2;
    float fc, x1, x2, y1, y2;

public:
    TSTone() = default;
    ~TSTone() = default;

    void Init();
    
    float Process(float in);

    void setFreq(float freq);
};

#endif // TSTone_H