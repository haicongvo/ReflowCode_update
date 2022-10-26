#include "pincfg.h"

void PINCFG::GPIosetup(void)
{
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);

  pinMode(THERM_PIN_1, INPUT);
  pinMode(THERM_PIN_2, INPUT);

  pinMode(MENU_BUTTON, INPUT);
  pinMode(OK_BUTTON, INPUT);
  pinMode(UP_BUTTON, INPUT);
  pinMode(DW_BUTTON, INPUT);

  ledcSetup(SSR1_CHN, freq_commom, PWM_resolution);
  ledcSetup(SSR2_CHN, freq_commom, PWM_resolution);
  ledcSetup(BUZZER_CHN, buzzer_freq, PWM_resolution);
  
  ledcAttachPin(SSR1_PIN, SSR1_CHN);
  ledcAttachPin(SSR2_PIN, SSR2_CHN);
  ledcAttachPin(BUZZER_PIN, BUZZER_CHN);
}

void PINCFG::GPIOinit(void)
{
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, HIGH);

    digitalWrite(FAN_PIN, LOW);
}
