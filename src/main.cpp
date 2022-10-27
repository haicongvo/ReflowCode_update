#include <Arduino.h>
#include "pincfg.h"
#include "OledDisplay.h"
#include "Temp.h"
#include "controlPID.h"
#include "controlPeripheral.h"

PINCFG pinconfig;
OLED oledscreen;
TEMP readtemp;
PID pid;
DEVICE device;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinconfig.GPIosetup();
  pinconfig.GPIOinit();

  oledscreen.Init();
  // while(!InitOLed)
  // {
  //   device.UpdateLedStatus(!digitalRead(LED_R), offled, offled);
  //   delay(500);
  // }
  device.ClearLed();
  device.UpdateLedStatus(offled, onled, offled);
  oledscreen.IntroScreen();
  //Display main screen
  oledscreen.MainScreen();
  //Display info on main screen
  oledscreen.DisplayThermal1(readtemp.ReadThermal_1());
  oledscreen.DisplayThermal2(readtemp.ReadThermal_2());
  oledscreen.DisplaySetpoint(pid.PIDvalue.Setpoint);
  oledscreen.DisplayTableInfo();
  oledscreen.DisplayFanMonitor(false);
  oledscreen.ResetTimeCount();
}

void loop() {
  // put your main code here, to run repeatedly:
  oledscreen.DisplayFanMonitor(true);
  delay(1000);
}