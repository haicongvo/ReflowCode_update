#ifndef _Temp_h_
#define _Temp_h_

#include <Arduino.h>

//-----THERMAL DATA---------//

#define VCC 3.3             // NodeMCU on board 3.3v vcc
#define R1 8870            // 4K7 ohm series resistor
#define adc_resolution 4095 // 12-bit adc
#define Bth 3950.0

class TEMP {
public:
    float ReadThermal_1(void);
    float ReadThermal_2(void);

    struct ReflowData
    {
        uint8_t RefHeatTemp = 4;
        uint8_t RefHeatTime = 1;

        int RefSoakTemp = 150;
        uint8_t RefSoakTime = 80;

        uint8_t RefRampTemp = 4;
        uint8_t RefRampTime = 1;

        int RefReflowTemp = 250;
        uint8_t RefReflowTime = 40;
    }ReflowData;
private:
};

#endif