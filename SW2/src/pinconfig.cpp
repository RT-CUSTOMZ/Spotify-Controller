#include "pinconfig.h"


void init_pins(){
    // Buttons to Input Pullup (savety precaution)
    pinMode(button_left, INPUT_PULLUP);
    pinMode(button_middle, INPUT_PULLUP);
    pinMode(button_right, INPUT_PULLUP);
    
    // LEDs to Outputs
    pinMode(led_orange, OUTPUT);
    pinMode(led_green, OUTPUT);
    pinMode(led_red_pin, OUTPUT);
}