#ifndef _OledDisplay_h_
#define _OledDisplay_h_

#include <Arduino.h>

//---------- DISPLAY INIT ---------------//
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C

class OLED {
public:
    bool Init(void);
    void IntroScreen(void);
    // display in main screen
    void MainScreen(void);
    void DisplayThermal1(float temperature);
    void DisplayThermal2(float temperature);
    void DisplaySetpoint(float temperature);
    void DisplayTableInfo(void);
    void DisplayTimeSoakStatus(uint8_t time);
    void DisplayTimeReflowStatus(uint8_t time);
    void DisplayFanMonitor(bool enable);
    void DisplayHeatIcon(bool displayicon);

    struct DisplayInfo
    {
        bool enableFanIcon = false;
    }DisplayInfo;
private:
    bool EnableChangeFanIcon = false;
};

#endif