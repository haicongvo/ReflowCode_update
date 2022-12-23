#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "OledDisplay.h"
#include "Temp.h"
#include "image.h"
#include "controlPeripheral.h"
#include "pincfg.h"
#include "controlPID.h"
#include "variableComom.h"


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
TEMP TempData;
DEVICE devicecontrol;
PID pidvalue;

bool OLED::Init(void)
{
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) return false;
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.clearDisplay();
    display.display();
    return true;
}

void OLED::ClearAllScreen(void)
{
    display.clearDisplay();
    display.display();
}

void OLED::IntroScreen(void)
{
    // display XY axis
    display.fillTriangle(0, 6, 6, 6, 3, 0, SSD1306_WHITE);
    display.drawLine(3, 7, 3, 40, SSD1306_WHITE);
    display.drawLine(3, 40, 121, 40, SSD1306_WHITE);
    display.fillTriangle(122, 37, 122, 43, 127, 40, SSD1306_WHITE);
    //display chart
    display.drawLine(6, 37, 30, 15, SSD1306_WHITE);
    display.drawLine(30, 15, 60, 15, SSD1306_WHITE);
    display.drawLine(60, 15, 80, 5, SSD1306_WHITE);
    display.drawLine(80, 5, 95, 5, SSD1306_WHITE);
    display.drawLine(95, 5, 119, 37, SSD1306_WHITE);
    //fill chart
    display.fillTriangle(6, 37, 30, 15, 30, 37, SSD1306_WHITE);
    display.fillRoundRect(30, 15, 65, 23, 0, SSD1306_WHITE);
    display.fillTriangle(60, 15, 80, 5, 80, 15, SSD1306_WHITE);
    display.fillRoundRect(80, 5, 15, 20, 0, SSD1306_WHITE);
    display.fillTriangle(95, 5, 95, 37, 119, 37, SSD1306_WHITE);

    display.setCursor(10, 48);
    display.print("SMD REFLOW MACHINE");
    display.setCursor(25, 56);
    display.print("made by V.C.H");
    display.display();

    delay(2000);

    display.clearDisplay();
    display.display();
}

void OLED::MainScreen(void)
{
    //--THERMAL 1--//
    display.setCursor(0, 12);
    display.print("T1:");
    //--THERMAL 2--//
    display.setCursor(0, 22);
    display.print("T2:");
    //--SETPOINT--//
    display.setCursor(0, 32);
    display.print("SP:");
    //-- TABLE INFO --//
    display.setCursor(52, 2);
    display.print("STAGE");
    display.setCursor(90, 2);
    display.print((char)247);
    display.print("C");
    display.setCursor(116, 2);
    display.print("S");
    //-- STAGE --//
    if(RunMode == REFLOW_MODE)
    {
        display.setCursor(58, 12);
        display.print("HEAT");
        display.setCursor(58, 22);
        display.print("SOAK");
        display.setCursor(58, 32);
        display.print("RAMP");
        display.setCursor(58, 42);
        display.print("RELF");
        display.setCursor(58, 52);
        display.print("COOL");
    }
    else if(RunMode == HEATER_MODE)
    {
        display.setCursor(58, 12);
        display.print("HEAT");
    }
    //-- Draw vertical line --//
    display.drawLine(50, 0, 50, 59, SSD1306_WHITE);
    display.drawLine(56, 10, 56, 59, SSD1306_WHITE);
    display.drawLine(82, 0, 82, 59, SSD1306_WHITE);
    display.drawLine(108, 0, 108, 49, SSD1306_WHITE);
    display.drawLine(127, 0, 127, 59, SSD1306_WHITE);
    //-- Draw horizontal line --//
    display.drawLine(50, 0, 127, 0, SSD1306_WHITE);
    display.drawLine(50, 10, 127, 10, SSD1306_WHITE);
    display.drawLine(50, 20, 127, 20, SSD1306_WHITE);
    display.drawLine(50, 30, 127, 30, SSD1306_WHITE);
    display.drawLine(50, 40, 127, 40, SSD1306_WHITE);
    display.drawLine(50, 50, 127, 50, SSD1306_WHITE);
    display.drawLine(50, 60, 127, 60, SSD1306_WHITE);
    //-- Draw fan icon --//
    DisplayFanMonitor(false);
    //--display run mode --//
    DisplayModeRun(RunMode);

    display.display();
}

void OLED::DisplayThermal1(float temperature)
{
    //clean value on display
    display.fillRoundRect(18, 12, 30, 7, 0, SSD1306_BLACK);
    //Display new value
    display.setCursor(18, 12);
    if(temperature <= 1.0)
    {
        display.print("NaN");
    }
    else if(temperature >= 400)
    {
        display.print("Err");
    }
    else
    {
        display.print((int)temperature);
        display.print((char)247);
        display.print("C");
    }
    display.display();
}

void OLED::DisplayThermal2(float temperature)
{
    //clean value on display
    display.fillRoundRect(18, 22, 30, 7, 0, SSD1306_BLACK);
    //Display new value
    display.setCursor(18, 22);
    if(temperature <= 1.0)
    {
        display.print("NaN");
    }
    else if(temperature >= 400)
    {
        display.print("Err");
    }
    else
    {
        display.print((int)temperature);
        display.print((char)247);
        display.print("C");
    }
    display.display();
}

void OLED::DisplaySetpoint(float temperature)
{
    //clean value on display
    display.fillRoundRect(18, 32, 30, 7, 0, SSD1306_BLACK);
    //Display new value
    display.setCursor(18, 32);
    display.print((int)temperature);
    display.print((char)247);
    display.print("C");
    display.display();
}

void OLED::DisplayTableInfo(void)
{
    if(RunMode == REFLOW_MODE)
    {
        display.setCursor(92, 12);
        display.print(RefHeatTemp);
        display.setCursor(116, 12);
        display.print(RefHeatTime);

        display.setCursor(86, 22);
        display.print(RefSoakTemp);
        //clean value on display
        display.fillRoundRect(109, 21, 18, 9, 0, SSD1306_BLACK);
        display.setCursor(112, 22);
        display.print(RefSoakTime);

        display.setCursor(92, 32);
        display.print(RefRampTemp);
        display.setCursor(116, 32);
        display.print(RefRampTime);

        display.setCursor(86, 42);
        display.print(RefReflowTemp);
        //clean value on display
        display.fillRoundRect(109, 41, 18, 9, 0, SSD1306_BLACK);
        display.setCursor(112, 42);
        display.print(RefReflowTime);
    }
    else if(RunMode == HEATER_MODE)
    {
        display.setCursor(92, 12);
        display.print(HeatTemp);
        display.setCursor(116, 12);
        display.print(HeatDelayTime);
    }
    display.display();
}

void OLED::DisplayTimeSoakStatus(uint8_t time)
{
    //clean value on display
    display.fillRoundRect(109, 21, 18, 9, 0, SSD1306_WHITE);
    //update new value
    display.setTextColor(SSD1306_BLACK);
    display.setCursor(112, 22);
    display.print(time);
    display.setTextColor(SSD1306_WHITE);
    display.display();
}

void OLED::DisplayTimeReflowStatus(uint8_t time)
{
    //clean value on display
    display.fillRoundRect(109, 41, 18, 9, 0, SSD1306_WHITE);
    //update new value
    display.setTextColor(SSD1306_BLACK);
    display.setCursor(112, 42);
    display.print(time);
    display.setTextColor(SSD1306_WHITE);
    display.display();
}

void OLED::DisplayFanMonitor(bool enable)
{
    display.fillRoundRect(0, 45, 16, 16, 0, SSD1306_BLACK);// clear display area
    if(enable)
    {
        EnableChangeFanIcon = !EnableChangeFanIcon;
        if(EnableChangeFanIcon) display.drawBitmap(0, 45, cool1, 16, 16, SSD1306_WHITE);
        else display.drawBitmap(0, 45, cool2, 16, 16, SSD1306_WHITE);
    }
    else
    {
        display.drawBitmap(0, 45, cool1, 16, 16, SSD1306_WHITE);
    }
    display.display();
}

void OLED::DisplayHeatIcon(bool displayicon)
{
    if(displayicon) display.drawBitmap(18, 38, warning, 32, 32, SSD1306_WHITE);
    else display.fillRoundRect(18, 45, 32, 32, 0, SSD1306_BLACK);// clear display area
    display.display();
}

void OLED::DisplayModeRun(uint8_t ModeNumber)
{
    //clean value on display
    display.fillRoundRect(0, 0, 40, 7, 0, SSD1306_BLACK);
    //Display new value
    display.setCursor(6, 0);
    switch(ModeNumber)
    {
        case 0:
        display.print("HEATED");
        break;
        case 1:
        display.print("REFLOW");
        break;
        default:
        break;
    }
    display.display();
}

void OLED::DisplayReflowModeStatus(uint8_t stage)
{
    EnableBlindReflowModeStatus = !EnableBlindReflowModeStatus;
    // clear display
    if(EnableBlindReflowModeStatus)
    {
        switch(LastReflowModeStatus)
        {
        case 1: // HEAT
            display.fillRoundRect(52, 12, 3, 7, 0, SSD1306_BLACK);
            devicecontrol.ClearLed();
            break;
        case 2: // SOAK
            display.fillRoundRect(52, 22, 3, 7, 0, SSD1306_BLACK);
            devicecontrol.ClearLed();
            break;
        case 3: // RAMP
            display.fillRoundRect(52, 32, 3, 7, 0, SSD1306_BLACK);
            devicecontrol.ClearLed();
            break;
        case 4: // REFLOW
            display.fillRoundRect(52, 42, 3, 7, 0, SSD1306_BLACK);
            devicecontrol.ClearLed();
            break;
        case 5: // COOL
            display.fillRoundRect(52, 52, 3, 7, 0, SSD1306_BLACK);
            devicecontrol.ClearLed();
            break;
        default:
            break;
        }
    }
    // display
    else
    {
        switch(stage)
        {
        case 1: // HEAT
            display.fillRoundRect(52, 12, 3, 7, 0, SSD1306_WHITE);
            devicecontrol.UpdateLedStatus(offled, onled, onled); // cyan
            break;
        case 2: // SOAK
            display.fillRoundRect(52, 22, 3, 7, 0, SSD1306_WHITE);
            devicecontrol.UpdateLedStatus(onled, onled, offled); // yellow
            break;
        case 3: // RAMP
            display.fillRoundRect(52, 32, 3, 7, 0, SSD1306_WHITE);
            devicecontrol.UpdateLedStatus(onled, offled, onled); // violet
            break;
        case 4: // REFLOW
            display.fillRoundRect(52, 42, 3, 7, 0, SSD1306_WHITE);
            devicecontrol.UpdateLedStatus(onled, offled, offled); // red
            break;
        case 5: // COOL
            display.fillRoundRect(52, 52, 3, 7, 0, SSD1306_WHITE);
            devicecontrol.UpdateLedStatus(offled, offled, onled); // blue
            break;
        default:
            break;
        }
    }
    LastReflowModeStatus = stage;
    display.display();
}

void OLED::DisplayTimeCount(uint16_t time)
{
    display.fillRoundRect(92, 52, 28, 7, 0, SSD1306_BLACK);// clear display area
    display.setCursor(92, 52);

    uint8_t second = (uint8_t)(time % 60);
    uint8_t minute = (uint8_t)((time / 60) % 60);
    display.print(minute);
    display.print(":");
    display.print(second);
    display.display();
}

void OLED::ResetTimeCount(void)
{
    DisplayTimeCount(0);
}

void OLED::DisplaySettingScreen(void)
{
    display.setCursor(40,0);
    display.print("SETTING");
    display.drawLine(0, 5, 38, 5, SSD1306_WHITE);
    display.drawLine(84, 5, 127, 5, SSD1306_WHITE);
    display.setCursor(10,10);
    display.print("MODE SELECTION");
    display.setCursor(10, 20);
    display.print("BUZZER ON/OFF");
    display.setCursor(10, 30);
    display.print("FAN ON/OFF");
    display.setCursor(10, 40);
    display.print("P.I.D SETTING");
    display.setCursor(10, 50);
    display.print("P.I.D TUNNING");
    display.display();
}

void OLED::DisplaySettingSelection(uint8_t currentselect)
{
    //clear display
  switch(LastSettingSelecttion)
  {
    case 1:
      display.fillRoundRect(0, 10, 7, 7, 0, SSD1306_BLACK);
      break;
    case 2:
      display.fillRoundRect(0, 20, 7, 7, 0, SSD1306_BLACK);
      break;
    case 3:
      display.fillRoundRect(0, 30, 7, 7, 0, SSD1306_BLACK);
      break;
    case 4:
      display.fillRoundRect(0, 40, 7, 7, 0, SSD1306_BLACK);
      break;
    case 5:
      display.fillRoundRect(0, 50, 7, 7, 0, SSD1306_BLACK);
      break;
    default:
      break;
  }
  // display
  switch(currentselect)
  {
    case 1:
      display.drawTriangle(0, 10, 6, 13, 0, 16, SSD1306_WHITE);
      break;
    case 2:
      display.drawTriangle(0, 20, 6, 23, 0, 26, SSD1306_WHITE);
      break;
    case 3:
      display.drawTriangle(0, 30, 6, 33, 0, 36, SSD1306_WHITE);
      break;
    case 4:
      display.drawTriangle(0, 40, 6, 43, 0, 46, SSD1306_WHITE);
      break;
    case 5:
      display.drawTriangle(0, 50, 6, 53, 0, 56, SSD1306_WHITE);
      break;
    default:
      break;
  }
  LastSettingSelecttion = currentselect;
  display.display();
}

void OLED::DisplayModeSelectionScreen(void)
{
    display.setCursor(30,0);
    display.print("MODE SELECT");
    display.drawLine(0, 5, 26, 5, SSD1306_WHITE);
    display.drawLine(98, 5, 127, 5, SSD1306_WHITE);

    display.setCursor(10,10);
    display.print("HEAT MODE");
    display.setCursor(10,20);
    display.print("REFLOW MODE");
    display.setCursor(10,30);
    display.print("CANCEL");
    display.display();
}

void OLED::DisplayBuzzerOnOffScreen(void)
{
    display.setCursor(21,0);
    display.print("BUZZER SETTING");
    display.drawLine(0, 5, 17, 5, SSD1306_WHITE);
    display.drawLine(109, 5, 127, 5, SSD1306_WHITE);

    display.setCursor(10,10);
    display.print("ON BUZZER");
    display.setCursor(10,20);
    display.print("OFF BUZZER");
    display.setCursor(10,30);
    display.print("CANCEL");
    display.display();
}

void OLED::DisplayFanOnOffScreen(void)
{
    display.setCursor(30,0);
    display.print("FAN SETTING");
    display.drawLine(0, 5, 26, 5, SSD1306_WHITE);
    display.drawLine(100, 5, 127, 5, SSD1306_WHITE);

    display.setCursor(10,10);
    display.print("AUTO");
    display.setCursor(10,20);
    display.print("ON FAN");
    display.setCursor(10,30);
    display.print("OFF FAN");
    display.setCursor(10,40);
    display.print("CANCEL");
    display.display();
}

void OLED::DisplayPIDSettingScreen(void)
{
    display.setCursor(24,0);
    display.print("P.I.D SETTING");
    display.drawLine(0, 5, 20, 5, SSD1306_WHITE);
    display.drawLine(106, 5, 127, 5, SSD1306_WHITE);

    display.setCursor(10,10);
    display.print("P Value: ");
    display.print(Kp);
    display.setCursor(10,20);
    display.print("I Value: ");
    display.print(Ki);
    display.setCursor(10,30);
    display.print("D Value: ");
    display.print(Kd);
    display.setCursor(10,40);
    display.print("CANCEL");
    display.display();
}

void OLED::DisplayPIDChangeValue(uint8_t CurentChangePIDValue)
{
    //clear display
    switch(LastChangePIDValue)
    {
        case P_CHANGE: //change P value
            display.fillRoundRect(64, 10, 100, 7, 0, SSD1306_BLACK);
            break;
        case I_CHANGE:// change I value
            display.fillRoundRect(64, 20, 100, 7, 0, SSD1306_BLACK);
            break;
        case D_CHANGE:// change D value
            display.fillRoundRect(64, 30, 100, 7, 0, SSD1306_BLACK);
            break;
        default:
            break;
    }

    //display value
    switch(CurentChangePIDValue)
    {
    case P_CHANGE:
        display.setCursor(64,10);
        display.print(KpTemp);
        break;
    case I_CHANGE:
        display.setCursor(64,20);
        display.print(KiTemp);
        break;
    case D_CHANGE:
        display.setCursor(64,30);
        display.print(KdTemp);
        break;
    default:
        break;
    }
    LastChangePIDValue = CurentChangePIDValue;
    display.display();
}

void OLED::ClearDisplayPIDValue(uint8_t choose)
{
    switch(choose)
    {
        case P_CHANGE: //change P value
            display.fillRoundRect(64, 10, 100, 7, 0, SSD1306_BLACK);
            break;
        case I_CHANGE:// change I value
            display.fillRoundRect(64, 20, 100, 7, 0, SSD1306_BLACK);
            break;
        case D_CHANGE:// change D value
            display.fillRoundRect(64, 30, 100, 7, 0, SSD1306_BLACK);
            break;
        default:
            break;
    }
    LastChangePIDValue = 0;
    display.display();
}