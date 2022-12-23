#ifndef _controlScreen_h_
#define _controlScreen_h_

#include <Arduino.h>

class DISPLAYSCREEN {
public:
    void ScreenInit(void);

    void SettingAndMainScreenDisplay(void);
    void WhenMainScreenDisplay(void);
    void SelectItemInSetting(void);
    void AcceptSettingSelection(void);

    void ModeSelect(void);
    void BuzzerSelect(void);
    void FanSelect(void);
    void PIDChange(void);

    void ResetValue(void);
    void ReturnSettingScreen(void);

    void SettingTableInfo(void);

private:

    bool ScreenSettingMode = false;
    bool ChangeScreen = false;
    bool ModeScreenInto = false;

    // SETTING SELECTION //
    uint8_t SettingSelection = 1;

    // PID temp value
    float KpValueTemp = 0;
    float KiValueTemp = 0;
    float KdValueTemp = 0;

    // setting table information
    uint8_t SettingTableInfoCount = 0;
    bool AcceptSettingTableInfo = false;
};

#endif