#pragma once

#ifndef DistHP_H
#define DistHP_H

class DistHP {
private:
    // static const int MWSPT_NSEC = 3;
    // const int NL[MWSPT_NSEC] = { 1,3,1 };
    // const float NUM[MWSPT_NSEC][3] = {
    // {
    //     0.03628773987,              0,              0 
    // },
    // {
    //                 1,              0,             -1 
    // },
    // {
    //                 1,              0,              0 
    // }
    // };
    // const int DL[MWSPT_NSEC] = { 1,3,1 };
    // const float DEN[MWSPT_NSEC][3] = {
    // {
    //                 1,              0,              0 
    // },
    // {
    //                 1,    -1.91554606,   0.9274244905 
    // },
    // {
    //                 1,              0,              0 
    // }
    // };
    static const int MWSPT_NSEC = 3;
    const int NL[MWSPT_NSEC] = { 1,2,1 };
    const float NUM[MWSPT_NSEC][2] = {
   {
     0.9989667535,              0 
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
                1,  -0.9979334474 
  },
  {
                1,              0 
  }
};
    float input_buffer[MWSPT_NSEC][2];
    float output_buffer[MWSPT_NSEC][2];

public:
    DistHP() = default;                
    ~DistHP() = default;

    void Init();
    
    float Process(float in);
};

#endif // DistHP_H