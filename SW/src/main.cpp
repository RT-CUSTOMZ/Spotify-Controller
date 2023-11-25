#include <Arduino.h>
#include "hal/led-hal.h"
#include "hal/button-hal.h"
#include "hal/wifi-hal.h"
#include "hal/encoder-hal.h"
#include "hal/display-hal.h"
#include "pinconfig.h"
#include "periphery/button-play-and-pause.h"


Button buttonLeft;
Button buttonMiddle;
Button buttonRight;



void setup() {

  init_pins();
  Serial.begin(460800); 
  delay(100);

  InitButtons();
  ledOn(led_yellow_pin);

  attachInterrupt(digitalPinToInterrupt(button_left), OnButtonPressRiseLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(button_left), OnButtonPressFallLeft, FALLING);

  attachInterrupt(digitalPinToInterrupt(button_middle), OnButtonPressRiseMiddle, RISING);
  attachInterrupt(digitalPinToInterrupt(button_middle), OnButtonPressFallMiddle, FALLING);

  attachInterrupt(digitalPinToInterrupt(button_right), OnButtonPressRiseRight, RISING);
  attachInterrupt(digitalPinToInterrupt(button_right), OnButtonPressFallRight, FALLING);  
}

void loop() {
  readEncoder();
  printDelta();

}


