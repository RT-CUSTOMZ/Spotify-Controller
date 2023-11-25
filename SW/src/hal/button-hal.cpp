#include "button-hal.h"
#include "pinconfig.h"
#include <Arduino.h>
#include "led-hal.h"

extern Button buttonLeft;
extern Button buttonMiddle;
extern Button buttonRight;

bool Button::DebouncedButton(uint16_t ms_to_ignore_interrupt){
    if(millis()-Button::GetTimeLastPressed()>ms_to_ignore_interrupt){
        if((true == Button::GetIsPressed()) 
        && (true == Button::GetStateChanged())){
            Serial.printf("Pressed\n");
        }
        Button::SetTimeLastPressed();
    }
    return true;
}

void OnButtonPressRiseLeft() {
    Serial.printf("P1");
    ledOn(led_dual_green);
    buttonLeft.SetStateChanged(true);
    buttonLeft.SetIsPressed(true);
}

void OnButtonPressFallLeft() {
    buttonLeft.SetStateChanged(true);
    buttonLeft.SetIsPressed(false);
}

void OnButtonPressRiseMiddle() {
    Serial.printf("P2");
    buttonMiddle.SetStateChanged(true);
    buttonMiddle.SetIsPressed(true);
}

void OnButtonPressFallMiddle() {
    buttonMiddle.SetStateChanged(true);
    buttonMiddle.SetIsPressed(false);
}

void OnButtonPressRiseRight() {
    Serial.printf("P3");
    buttonRight.SetStateChanged(true);
    buttonRight.SetIsPressed(true);
}

void OnButtonPressFallRight() {
    buttonRight.SetStateChanged(true);
    buttonRight.SetIsPressed(false);
}

void InitButtons(){

    attachInterrupt(digitalPinToInterrupt(button_left), OnButtonPressRiseLeft, RISING);
    attachInterrupt(digitalPinToInterrupt(button_left), OnButtonPressFallLeft, FALLING);

    attachInterrupt(digitalPinToInterrupt(button_middle), OnButtonPressRiseMiddle, RISING);
    attachInterrupt(digitalPinToInterrupt(button_middle), OnButtonPressFallMiddle, FALLING);

    attachInterrupt(digitalPinToInterrupt(button_right), OnButtonPressRiseRight, RISING);
    attachInterrupt(digitalPinToInterrupt(button_right), OnButtonPressFallRight, FALLING);

}


// void button_loop(){
//     if(button_left_pressed ==0 && button_left_changed == 1){
//         Serial.printf("P1\n");
//         ledOn(led_dual_green);
//     } else if(button_left_pressed ==1 && button_left_changed == 1){
//         Serial.printf("NP1\n");
//         ledOff(led_dual_green);
//     }
//     button_left_changed = 0;

//     if((button_middle_pressed ==0) && (button_middle_changed == 1)){
//         Serial.printf("P2\n");
//         ledOn(led_dual_red);
//     } else if((button_middle_pressed == 1) && (button_middle_changed == 1)){
//         Serial.printf("NP2\n");
//         ledOff(led_dual_red);
//     }
//     button_middle_changed = 0;

//     if((button_right_pressed ==0) && (button_right_changed == 1)){
//         Serial.printf("P3\n");
//         ledOn(led_yellow_pin);
//     } else if((button_right_pressed == 1) && (button_right_changed == 1)){
//         Serial.printf("NP3\n");
//         ledOff(led_yellow_pin);
//     }
//     button_right_changed = 0;
// }