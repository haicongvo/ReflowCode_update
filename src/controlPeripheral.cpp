#include "controlPeripheral.h"
#include "pincfg.h"

void DEVICE::UpdateLedStatus(bool red, bool green, bool blue)
{
    digitalWrite(LED_R, red);
    digitalWrite(LED_G, green);
    digitalWrite(LED_B, blue);
}

void DEVICE::ClearLed(void)
{
    digitalWrite(LED_R, offled);
    digitalWrite(LED_G, offled);
    digitalWrite(LED_B, offled);
}