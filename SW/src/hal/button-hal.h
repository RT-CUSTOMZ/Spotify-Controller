#pragma once
#include "pinconfig.h"

class Button{
    private:
        bool button_is_pressed = 0;
        bool button_state_changed = 0;
        unsigned long time_since_last_button_pressed = 0;

    public:
        inline bool GetIsPressed(){
            return button_is_pressed;
        }

        inline bool SetIsPressed(bool value){
            return button_is_pressed = value;
        }

        inline bool SetStateChanged(bool value){
            return button_state_changed = value;
        }

        inline bool GetStateChanged(){
            return button_state_changed;
        }

        inline bool SetTimeLastPressed(){
            return (time_since_last_button_pressed = millis())?true:false;
        }

        inline unsigned long GetTimeLastPressed(){
            return time_since_last_button_pressed;
        }

};

void OnButtonPressRiseLeft();
void OnButtonPressFallLeft();
void OnButtonPressRiseMiddle();
void OnButtonPressFallMiddle();
void OnButtonPressRiseRight();
void OnButtonPressFallRight();
void InitButtons();

