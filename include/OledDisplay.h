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
    void ClearAllScreen(void);
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
    void DisplayModeRun(uint8_t ModeNumber);
    void DisplayReflowModeStatus(uint8_t stage);
    void DisplayTimeCount(uint16_t time);
    void ResetTimeCount(void);
    // display in setting screen
    void DisplaySettingScreen(void);
    void DisplaySettingSelection(uint8_t currentselect);
    void DisplayModeSelectionScreen(void);
    void DisplayBuzzerOnOffScreen(void);
    void DisplayFanOnOffScreen(void);
    void DisplayPIDSettingScreen(void);
    void DisplayPIDChangeValue(uint8_t CurentChangePIDValue);
    void ClearDisplayPIDValue(uint8_t choose);

    struct DisplayInfo
    {
        bool EnableFanIcon = false;
    }DisplayInfo;
private:
    bool EnableChangeFanIcon = false;
    bool EnableBlindReflowModeStatus = false;
    bool FistClearPIDValue = false;

    uint8_t LastReflowModeStatus = 0;
    
    uint8_t LastSettingSelecttion = 0;

    uint8_t LastChangePIDValue = 0;

};

#endif