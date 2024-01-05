#define SSD1306_NO_SPLASH
#include <Arduino.h>

#include "hal/led-hal.h"
#include "hal/button-hal.h"
#include "pinconfig.h"



void setup() {

  InitPins();
  Serial.begin(460800); 
  
  while (!Serial)
     delay(10);
  
  ledOn(led_dual_green);

  InitButtons(); 
}

void loop() {
  ButtonLoop();
}



