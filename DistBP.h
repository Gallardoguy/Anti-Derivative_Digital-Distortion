#pragma once

#ifndef DistBP_H
#define DistBP_H

class DistBP {
private:
    static const int MWSPT_NSEC = 5;
    const int NL[MWSPT_NSEC] = { 1,3,1,3,1 };
    const float NUM[MWSPT_NSEC][3] = {
    {
        0.1303463876,              0,              0 
    },
    {
                    1,              0,             -1 
    },
    {
        0.1303463876,              0,              0 
    },
    {
                    1,              0,             -1 
    },
    {
                    1,              0,              0 
    }
    };
    const int DL[MWSPT_NSEC] = { 1,3,1,3,1 };
    const float DEN[MWSPT_NSEC][3] = {
    {
                    1,              0,              0 
    },
    {
                    1,   -1.999370813,   0.9993710518 
    },
    {
                    1,              0,              0 
    },
    {
                    1,   -1.599311471,    0.667294085 
    },
    {
                    1,              0,              0 
    }
    };
    float input_buffer[MWSPT_NSEC][3];
    float output_buffer[MWSPT_NSEC][3];

public:
    DistBP() = default;                
    ~DistBP() = default;

    void Init();
    
    float Process(float in);
};

#endif // DistBP_H