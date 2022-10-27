#ifndef _controlPeripheral_h_
#define _controlPeripheral_h_

#include <Arduino.h>

class DEVICE {
public:
    void UpdateLedStatus(bool red, bool green, bool blue);
    void ClearLed(void);
private:
};

#endif
