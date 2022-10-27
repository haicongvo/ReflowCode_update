#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "OledDisplay.h"
#include "Temp.h"
#include "image.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
TEMP TempData;

bool OLED::Init(void)
{
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) return false;
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.clearDisplay();
    display.display();
    return true;
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
    //Update_fan_status(false);

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
    display.setCursor(92, 12);
    display.print(TempData.ReflowData.RefHeatTemp);
    display.setCursor(116, 12);
    display.print(TempData.ReflowData.RefHeatTime);

    display.setCursor(86, 22);
    display.print(TempData.ReflowData.RefSoakTemp);
    //clean value on display
    display.fillRoundRect(109, 21, 18, 9, 0, SSD1306_BLACK);
    display.setCursor(112, 22);
    display.print(TempData.ReflowData.RefSoakTime);

    display.setCursor(92, 32);
    display.print(TempData.ReflowData.RefRampTemp);
    display.setCursor(116, 32);
    display.print(TempData.ReflowData.RefRampTime);

    display.setCursor(86, 42);
    display.print(TempData.ReflowData.RefReflowTemp);
    //clean value on display
    display.fillRoundRect(109, 41, 18, 9, 0, SSD1306_BLACK);
    display.setCursor(112, 42);
    display.print(TempData.ReflowData.RefReflowTime);
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
}

void OLED::DisplayHeatIcon(bool displayicon)
{
    if(displayicon) display.drawBitmap(18, 38, warning, 32, 32, SSD1306_WHITE);
    else display.fillRoundRect(18, 45, 32, 32, 0, SSD1306_BLACK);// clear display area
}