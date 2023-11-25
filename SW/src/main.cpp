#include <Arduino.h>
#include "hal/led-hal.h"
#include "hal/button-hal.h"
#include "hal/wifi-hal.h"
#include "hal/encoder-hal.h"
#include "hal/display-hal.h"
#include "pinconfig.h"
#include "spotify_functions/button-play-and-pause.h"


Button buttonLeft;
Button buttonMiddle;
Button buttonRight;
Button buttonEncoder;


void setup() {

  init_pins();
  Serial.begin(460800); 
  delay(100);

  InitButtons();
  ledOn(led_yellow_pin);
  
  
   
}

void loop() {
  readEncoder();
  printDelta();

    if(HIGH == buttonLeft.GetStateChanged()){
        Serial.printf("B1\t%d\n", buttonLeft.ms.TimeDifference());
        buttonLeft.ms.SetLastPressed();
        buttonLeft.SetStateChanged(false);
    }

    if(HIGH == buttonMiddle.GetStateChanged()){
        Serial.printf("B2\t%d\n", buttonMiddle.ms.TimeDifference());
        buttonMiddle.ms.SetLastPressed();
        buttonMiddle.SetStateChanged(false);
    }

    if(HIGH == buttonRight.GetStateChanged()){
        Serial.printf("B3\t%d\n", buttonRight.ms.TimeDifference());
        buttonRight.ms.SetLastPressed();
        buttonRight.SetStateChanged(false);
    }

    if(HIGH == buttonEncoder.GetStateChanged()){
        Serial.printf("BE\t%d\n", buttonEncoder.ms.TimeDifference());
        buttonEncoder.ms.SetLastPressed();
        buttonEncoder.SetStateChanged(false);
    }

    // delay(1000);
}


