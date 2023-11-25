#include "button-hal.h"
#include "pinconfig.h"
#include <Arduino.h>
#include "led-hal.h"

extern Button buttonLeft;
extern Button buttonMiddle;
extern Button buttonRight;

const uint16_t time_to_change = 250;



void OnButtonPressFallLeft() {
    if((millis()-buttonLeft.GetTimeLastPressed())>time_to_change){

        Serial.printf("P1\t%d\n", millis()-buttonMiddle.GetTimeLastPressed());
        buttonLeft.SetStateChanged(true);
        buttonLeft.SetIsPressed(false);

        buttonLeft.SetTimeLastPressed();
    }
}

void OnButtonPressFallMiddle() {
    if((millis()-buttonMiddle.GetTimeLastPressed())>time_to_change){
        Serial.printf("P2\t%d\n", millis()-buttonMiddle.GetTimeLastPressed());

        buttonMiddle.SetStateChanged(true);
        buttonMiddle.SetIsPressed(false);

        buttonMiddle.SetTimeLastPressed();
    }
}

void OnButtonPressFallRight() {
    if((millis()-buttonRight.GetTimeLastPressed())>time_to_change){
        Serial.printf("P3\t%d\n", millis()-buttonMiddle.GetTimeLastPressed());
        buttonRight.SetStateChanged(true);
        buttonRight.SetIsPressed(false);

        buttonRight.SetTimeLastPressed();
    }
}

void InitButtons(){
    buttonLeft.SetTimeLastPressed();
    buttonMiddle.SetTimeLastPressed();
    buttonRight.SetTimeLastPressed();
    buttonRight.SetTimeLastPressed();
  attachInterrupt(digitalPinToInterrupt(button_left), OnButtonPressFallLeft, FALLING);
  attachInterrupt(digitalPinToInterrupt(button_middle), OnButtonPressFallMiddle, FALLING);
  attachInterrupt(digitalPinToInterrupt(button_right), OnButtonPressFallRight, FALLING);
}
