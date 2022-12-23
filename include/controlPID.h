#ifndef _controlPID_h_
#define _controlPID_h_

#include <Arduino.h>

class PID {
public:
    
    void PID_control(void);
private:
    float E , E1, E2, alpha, gamman, beta;
    float Output = 0, LastOutput = 0;
    float currentTemp_1 = 0, currentTemp_2 = 0;
    float T = 0.5;//thoi gian lay mau 0.5s
};

#endif