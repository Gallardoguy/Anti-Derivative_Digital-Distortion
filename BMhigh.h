#pragma once

#ifndef BMhigh_H
#define BMHigh_H

class BMhigh {
private:
    static const int MWSPT_NSEC = 3;
    const int NL[MWSPT_NSEC] = { 1,2,1 };
    const float NUM[MWSPT_NSEC][2] = {
    {
     0.9484700561,              0 
    },
    {
                    1,             -1 
    },
    {
                    1,              0 
    }
    };
    const int DL[MWSPT_NSEC] = { 1,2,1 };
    const float DEN[MWSPT_NSEC][2] = {
    {
                1,              0 
    },
    {
                    1,  -0.8969401121 
    },
    {
                    1,              0 
    }
    };
    float input_buffer[MWSPT_NSEC][2];
    float output_buffer[MWSPT_NSEC][2];

public:
    BMhigh() = default;                
    ~BMhigh() = default;

    void Init();
    
    float Process(float in);
};

#endif // BMhigh_H