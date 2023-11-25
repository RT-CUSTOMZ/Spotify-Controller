#include "button-hal.h"
#include "pinconfig.h"
#include <Arduino.h>
#include "led-hal.h"

Button buttonLeft;
Button buttonMiddle;
Button buttonRight;
Button buttonEncoder;

const uint16_t time_to_change = 250;


void OnButtonLeftPress() {
    if(buttonLeft.ms.TimeDifferenceOk(time_to_change)){
        buttonLeft.SetStateChanged(true);
    }
}

void OnButtonMiddlePress() {
    if(buttonMiddle.ms.TimeDifferenceOk(time_to_change)){
        buttonMiddle.SetStateChanged(true);
    }
}

void OnButtonRightPress() {
    if(buttonRight.ms.TimeDifferenceOk(time_to_change)){
        buttonRight.SetStateChanged(true);
    }
}
void OnButtonEncoderPress() {
    if(buttonEncoder.ms.TimeDifferenceOk(time_to_change)){
        buttonEncoder.SetStateChanged(true);
    }
}

void InitButtons(){
    buttonLeft.ms.SetLastPressed();
    buttonMiddle.ms.SetLastPressed();
    buttonRight.ms.SetLastPressed();
    buttonEncoder.ms.SetLastPressed();

    attachInterrupt(digitalPinToInterrupt(button_left), OnButtonLeftPress, FALLING);
    attachInterrupt(digitalPinToInterrupt(button_middle), OnButtonMiddlePress, FALLING);
    attachInterrupt(digitalPinToInterrupt(button_right), OnButtonRightPress, FALLING);
    attachInterrupt(digitalPinToInterrupt(encoder_sw), OnButtonEncoderPress, FALLING);
}

void ButtonLoop(){
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
}

