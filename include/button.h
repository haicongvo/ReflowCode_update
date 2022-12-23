#ifndef _button_h_
#define _button_h_

#include <Arduino.h>

class BUTTON {
public:
    void ReadAllButton(void);
    void ReadMenuButtonStatus(void);
    void ReadOKButtonStatus(void);
    void ReadUPButtonStatus(void);
    void ReadDWButtonStatus(void);

    bool ReadLongPressUpDutton(void);
    bool ReadLongPressDWDutton(void);

private:
    unsigned long debounceDuration = 60; // millis
    // MENU BUTTON
    bool lastMenuButtonState = 1;
    unsigned long lastTimeMenuButtonStateChanged = 0;
    // OK BUTTON
    bool lastOKButtonState = 1;
    unsigned long lastTimeOKButtonStateChanged = 0;
    // UP BUTTON
    bool lastUPButtonState = 1;
    unsigned long lastTimeUPButtonStateChanged = 0;
    // DW BUTTON
    bool lastDWButtonState = 1;
    unsigned long lastTimeDWButtonStateChanged = 0;
    // PRESS LONG
     unsigned long WaitTimeToRead = 100;
     unsigned long lastTimeUPButtonToRead = 0;
     unsigned long lastTimeDWButtonToRead = 0;
};

#endif