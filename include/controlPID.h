#ifndef _controlPID_h_
#define _controlPID_h_

class PID {
public:
    struct PIDvalue
    {
        float Kp = 1.2;
        float Ki = 0.15;
        float Kd = 2.5;

        float KpTemp = 0, KiTemp = 0, KdTemp = 0;
        float Setpoint = 30.0, CurrentTemp = 0;
    }PIDvalue;
    
    void PID_control(void);
private:
    float E , E1, E2, alpha, gamman, beta;
    float Output = 0, LastOutput = 0;
    float currentTemp_1 = 0, currentTemp_2 = 0;
    float T = 0.5;//thoi gian lay mau 0.5s
};

#endif