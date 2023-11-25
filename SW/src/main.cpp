#include <Arduino.h>
#include "hal/led-hal.h"
#include "hal/button-hal.h"
#include "hal/wifi-hal.h"
#include "hal/encoder-hal.h"
#include "hal/display-hal.h"
#include "pinconfig.h"
#include "spotify_functions/button-play-and-pause.h"


void setup() {

  init_pins();
  Serial.begin(460800); 
  delay(100);

  InitButtons();
  ledOn(led_yellow_pin); //Just so I know flashing worked
  
  
   
}

void loop() {
  readEncoder();
  printDelta();
  ButtonLoop();
}


