#include "pincfg.h"
#include "controlPID.h"
#include "Temp.h"
#include "variableComom.h"

TEMP ReadThermal;
void PID::PID_control()
{
    // select thermal to read
    currentTemp_1 = ReadThermal.ReadThermal_1();
    currentTemp_2 = ReadThermal.ReadThermal_2();
    if(currentTemp_1 <= 1.0) CurrentTemp = currentTemp_2;
    else CurrentTemp = currentTemp_1;

    E = Setpoint - CurrentTemp;
    alpha = (2 * T * Kp) + (Ki * T * T) + (2 * Kd);
    beta = (T * T * Ki) - (4 * Kd) - (2 * T * Kp);
    gamman = 2 * Kd;
    Output = (alpha * E + beta * E1 + gamman * E2 + 2 * T * LastOutput) / (2 * T);

    LastOutput = Output;
    E2 = E1;
    E1 = E;  
    
    if(Output > 255)  Output = 255;
    else if(Output <= 0) Output = 0;

    ledcWrite(SSR1_CHN, Output); // control relay SSR
}