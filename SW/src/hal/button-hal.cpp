#include "button-hal.h"
#include "pinconfig.h"
#include <Arduino.h>
#include "led-hal.h"

extern Button buttonLeft;
extern Button buttonMiddle;
extern Button buttonRight;
extern Button buttonEncoder;

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

