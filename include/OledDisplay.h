#ifndef _OledDisplay_h_
#define _OledDisplay_h_

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//---------- DISPLAY INIT ---------------//
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C

class OLED {
public:
    bool Init(void);
    void IntroScreen(void);
private:
};

#endif