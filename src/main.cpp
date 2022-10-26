#include "main.h"

PINCFG pinconfig;
OLED oledscreen;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinconfig.GPIosetup();
  pinconfig.GPIOinit();

  while(!oledscreen.Init()) 
  {
    Serial.println("SSD1306 allocation failed");
    delay(1000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}