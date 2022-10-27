#include "Temp.h"
#include "pincfg.h"
#include "controlPID.h"

float TEMP::ReadThermal_1(void)
{
    uint16_t adc_value;
    for(int i = 0; i < 10; i++)
    {
        adc_value += analogRead(THERM_PIN_1);
    }

    adc_value = adc_value / 10;
    
    double Vout, Rth, temperature; 

    Rth = R1 / (adc_resolution / (double)adc_value - 1);

    /*  Steinhart-Hart Thermistor Equation:
    *  Temperature in Kelvin = (T0*B) / (B + T0 * ln(R/R0'))
    */
    temperature = 1.0/ ((1.0 / (25.0 + 274.15)) + (log(Rth / 100000.0) / 3950.0));// Temperature in kelvin

    temperature = temperature - 274.15;  // Temperature in degree celsius 

    return temperature;
}

float TEMP::ReadThermal_2(void)
{
    uint16_t adc_value;
    for(int i = 0; i < 10; i++)
    {
        adc_value += analogRead(THERM_PIN_2);
    }

    adc_value = adc_value / 10;
    
    double Vout, Rth, temperature; 

    Rth = R1 / (adc_resolution / (double)adc_value - 1);

    /*  Steinhart-Hart Thermistor Equation:
    *  Temperature in Kelvin = (T0*B) / (B + T0 * ln(R/R0'))
    */
    temperature = 1.0/ ((1.0 / (25.0 + 274.15)) + (log(Rth / 100000.0) / 3950.0));// Temperature in kelvin

    temperature = temperature - 274.15;  // Temperature in degree celsius 

    return temperature; 
}