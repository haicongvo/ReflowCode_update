#include <Arduino.h>
#include "variableComom.h"
#include "pincfg.h"
#include "OledDisplay.h"
#include "Temp.h"
#include "controlPID.h"
#include "controlPeripheral.h"
#include "controlScreen.h"
#include "button.h"

PINCFG pinconfig;
OLED oledscreen;
TEMP readtemp;
PID pid;
DEVICE device;
DISPLAYSCREEN displayscreen;
BUTTON readbutton;

// BUTTON STATUS
bool MenuButtonPress = false; 
bool OKButtonPress = false; 
bool UPButtonPress = false; 
bool DWButtonPress = false;

uint8_t ModeRun = 0;
uint16_t RunTime = 0;

float Kp = 1.2;
float Ki = 0.15;
float Kd = 2.5;

float KpTemp = 0, KiTemp = 0, KdTemp = 0;
float Setpoint = 30.0, CurrentTemp = 0;

bool ModeSelection = false;
bool BuzzerOnOff = false;
bool FanOnOff = false;
bool PIDSetting = false;
bool PIDValueChange = false;

//reflow data
uint8_t RefHeatTemp = 4;
uint8_t RefHeatTime = 1;

int RefSoakTemp = 150;
uint8_t RefSoakTime = 80;

uint8_t RefRampTemp = 4;
uint8_t RefRampTime = 1;

int RefReflowTemp = 250;
uint8_t RefReflowTime = 40;

// heat data
uint8_t HeatTemp = 260;
uint8_t HeatDelayTime = 50;

//screen info
uint8_t SettingSelectionScreen = 1;

// setting data
uint8_t RunMode = HEATER_MODE;
uint8_t BuzzerMode = BUZZER_OFF;
uint8_t FanMode = FAN_OFF;
uint8_t PIDValueChangeSelect = 0;

// device status
bool FanStatus = OFF;
bool BuzzerStatus = OFF;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinconfig.GPIosetup();
  pinconfig.GPIOinit();

  displayscreen.ScreenInit();
  device.ClearLed();
  device.UpdateLedStatus(offled, onled, offled);
}

void loop() {
  // put your main code here, to run repeatedly:
  readbutton.ReadAllButton(); //read all button status
  displayscreen.SettingAndMainScreenDisplay();
  displayscreen.WhenMainScreenDisplay();
  displayscreen.SelectItemInSetting();
  displayscreen.AcceptSettingSelection();
  displayscreen.ModeSelect();
  displayscreen.BuzzerSelect();
  displayscreen.FanSelect();
  displayscreen.PIDChange();
}