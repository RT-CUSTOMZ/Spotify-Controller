#pragma once
#include <Arduino.h>

/*
    For debouncing purpose, each Button has to "know" when it was pressed last.
    Making the separation more easy, those functions were put into their own class.  
*/
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


/*
    Handles if a Button was pressed
*/
class Button{
    private:
        bool button_state_changed = 0;

    public:

        inline bool SetStateChanged(bool value){
            return button_state_changed = value;
        }

        inline bool GetStateChanged(){
            return button_state_changed;
        }

        Time ms;


};