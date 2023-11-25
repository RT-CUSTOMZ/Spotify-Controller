#pragma once
#include <Arduino.h>
class Time{
    unsigned long time_since_last_button_pressed = 0;

    public:
    inline bool SetLastPressed(){
        time_since_last_button_pressed = millis();
        return true;
    }

    inline unsigned long GetLastPressed(){
        return time_since_last_button_pressed;
    }

    inline unsigned long TimeDifference(){
        return (millis()-GetLastPressed());
    } 

    inline unsigned long TimeDifferenceOk(uint16_t time){
        return (TimeDifference()>time)?true:false;
    } 

};

class Button{
    private:
        bool button_is_pressed = 0;
        bool button_state_changed = 0;

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

        Time ms;


};