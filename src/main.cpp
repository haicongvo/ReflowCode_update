#include <Arduino.h>
#include "pincfg.h"
#include "OledDisplay.h"
#include "Temp.h"
#include "controlPID.h"

PINCFG pinconfig;
OLED oledscreen;
TEMP readtemp;
PID pid;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinconfig.GPIosetup();
  pinconfig.GPIOinit();

  while(!oledscreen.Init()) 
  {
    digitalWrite(LED_CAUTION, !digitalRead(LED_CAUTION));
    delay(500);
  }
  oledscreen.IntroScreen();
  //Display main screen
  oledscreen.MainScreen();
  //Display info on main screen
  oledscreen.DisplayThermal1(readtemp.ReadThermal_1());
  oledscreen.DisplayThermal2(readtemp.ReadThermal_2());
  oledscreen.DisplaySetpoint(pid.PIDvalue.Setpoint);
  oledscreen.DisplayTableInfo();

}

void loop() {
  // put your main code here, to run repeatedly:
  
}