#pragma once

#ifndef DistHPHM_H
#define DistHPHM_H

class DistHPHM {
private:
    static const int MWSPT_NSEC = 5;
    const int NL[MWSPT_NSEC] = { 1,3,1,3,1 };
    const float NUM[MWSPT_NSEC][3] = {
    {
     0.1233932674,              0,              0 
  },
  {
                1,              0,             -1 
  },
  {
     0.1233932674,              0,              0 
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
                1,    -1.99667263,   0.9966782928 
  },
  {
                1,              0,              0 
  },
  {
                1,   -1.624030471,   0.6850495338 
  },
  {
                1,              0,              0 
  }
};
    float input_buffer[MWSPT_NSEC][3];
    float output_buffer[MWSPT_NSEC][3];

public:
    DistHPHM() = default;                
    ~DistHPHM() = default;

    void Init();
    
    float Process(float in);
};

#endif // DistHPHM_H