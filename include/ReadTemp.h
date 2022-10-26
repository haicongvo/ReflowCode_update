#ifndef _ReadTemp_h_
#define _ReadTemp_h_

//-----THERMAL DATA---------//

#define VCC 3.3             // NodeMCU on board 3.3v vcc
#define R1 8870            // 4K7 ohm series resistor
#define adc_resolution 4095 // 12-bit adc
#define Bth 3950.0

class TEMP {
public:
    float ReadThermal_1(void);
    float ReadThermal_2(void);
private:
};

#endif