#include <Arduino.h>
#include "hal/led-hal.h"
#include "hal/button-hal.h"
#include "hal/wifi-hal.h"
#include "hal/encoder-hal.h"
#include "hal/display-hal.h"

#include "pinconfig.h"

bool button_left_pressed = 0;
bool button_left_changed = 0;

bool button_middle_pressed = 0;
bool button_middle_changed = 0;

bool button_right_pressed = 0;
bool button_right_changed = 0;

void ButtonLeftIsPressed() {
  button_left_pressed = 1;
  button_left_changed = 1;
}

void ButtonLeftIsNotPressed() {
  button_left_pressed = 0;
  button_left_changed = 1;

}

void ButtonMiddleIsPressed() {
  button_middle_pressed = 1;
  button_middle_changed = 1;
}

void ButtonMiddleIsNotPressed() {
  button_middle_pressed = 0;
  button_middle_changed = 1;
}

void ButtonRightIsPressed() {
  button_right_pressed = 1;
  button_right_changed = 1;
}

void ButtonRightIsNotPressed() {
  button_right_pressed = 0;
  button_right_changed = 1;
}


void setup() {
  init_pins();
  // init_display();

  Serial.begin(460800);  

  attachInterrupt(digitalPinToInterrupt(button_left), ButtonLeftIsNotPressed, FALLING);
  attachInterrupt(digitalPinToInterrupt(button_left), ButtonLeftIsPressed, RISING);
  attachInterrupt(digitalPinToInterrupt(button_middle), ButtonMiddleIsNotPressed, FALLING);
  attachInterrupt(digitalPinToInterrupt(button_middle), ButtonMiddleIsPressed, RISING);
  attachInterrupt(digitalPinToInterrupt(button_right), ButtonRightIsNotPressed, FALLING);
  attachInterrupt(digitalPinToInterrupt(button_right), ButtonRightIsPressed, RISING);
}

void loop() {


  readEncoder();
  printDelta();
  
  // display_loop();
  // if(digitalRead(button_left)==LOW){
  //   digitalWrite(led_dual_green, HIGH);
  // } else {
  //   digitalWrite(led_dual_green, LOW);
  // }
  if(button_left_pressed ==0 && button_left_changed == 1){
      Serial.printf("P1\n");
      ledOn(led_dual_green);
  } else if(button_left_pressed ==1 && button_left_changed == 1){
      Serial.printf("NP1\n");
      ledOff(led_dual_green);
  }
  button_left_changed = 0;

  if((button_middle_pressed ==0) && (button_middle_changed == 1)){
      Serial.printf("P2\n");
      ledOn(led_dual_red);
  } else if((button_middle_pressed == 1) && (button_middle_changed == 1)){
      Serial.printf("NP2\n");
      ledOff(led_dual_red);
  }
  button_middle_changed = 0;

  if((button_right_pressed ==0) && (button_right_changed == 1)){
      Serial.printf("P3\n");
      ledOn(led_yellow_pin);
  } else if((button_right_pressed == 1) && (button_right_changed == 1)){
      Serial.printf("NP3\n");
      ledOff(led_yellow_pin);
  }
  button_right_changed = 0;

}


