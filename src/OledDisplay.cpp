#include "OledDisplay.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool OLED::Init(void)
{
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) return false;
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    return true;
}
