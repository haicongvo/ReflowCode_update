#include "pincfg.h"
#include "controlPID.h"
#include "Temp.h"

TEMP ReadThermal;
void PID::PID_control()
{
    // select thermal to read
    currentTemp_1 = ReadThermal.ReadThermal_1();
    currentTemp_2 = ReadThermal.ReadThermal_2();
    if(currentTemp_1 <= 1.0) PIDvalue.CurrentTemp = currentTemp_2;
    else PIDvalue.CurrentTemp = currentTemp_1;

    E = PIDvalue.Setpoint - PIDvalue.CurrentTemp;
    alpha = (2 * T * PIDvalue.Kp) + (PIDvalue.Ki * T * T) + (2 * PIDvalue.Kd);
    beta = (T * T * PIDvalue.Ki) - (4 * PIDvalue.Kd) - (2 * T * PIDvalue.Kp);
    gamman = 2 * PIDvalue.Kd;
    Output = (alpha * E + beta * E1 + gamman * E2 + 2 * T * LastOutput) / (2 * T);

    LastOutput = Output;
    E2 = E1;
    E1 = E;  
    
    if(Output > 255)  Output = 255;
    else if(Output <= 0) Output = 0;

    ledcWrite(SSR1_CHN, Output); // control relay SSR
}