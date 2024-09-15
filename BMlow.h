#pragma once

#ifndef BMlow_H
#define BMlow_H

class BMlow {
private:
    static const int MWSPT_NSEC = 3;
    const int NL[MWSPT_NSEC] = { 1,2,1 };
    const float NUM[MWSPT_NSEC][2] = {
    {
    0.02323783375,              0 
    },
    {
                    1,              1 
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
                    1,  -0.9535243511 
    },
    {
                    1,              0 
    }
    };
    float input_buffer[MWSPT_NSEC][2];
    float output_buffer[MWSPT_NSEC][2];

public:
    BMlow() = default;                
    ~BMlow() = default;

    void Init();
    
    float Process(float in);
};

#endif // BMhlow_H