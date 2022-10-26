#ifndef _pincfg_h_
#define _pincfg_h_

#include <Arduino.h>

#define LED_CAUTION 2
#define LED_R       12
#define LED_G       13
#define LED_B       14

#define onled       0
#define offled      1

#define THERM_PIN_1 36
#define THERM_PIN_2 39

#define MENU_BUTTON 34
#define OK_BUTTON   35
#define UP_BUTTON   32
#define DW_BUTTON   33

#define SSR1_PIN    16
#define SSR1_CHN    2
#define SSR2_PIN    17
#define SSR2_CHN    3
#define FAN_PIN     18

#define BUZZER_PIN  19
#define BUZZER_CHN  5
#define PWM_resolution 8
#define freq_commom 1000
#define buzzer_freq 2000


class PINCFG {
public:
    void GPIosetup(void);
    void GPIOinit(void);
private:
};

#endif //_pin_h_
