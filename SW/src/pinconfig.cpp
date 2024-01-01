#include "pinconfig.h"


void init_pins(){
    // Buttons to Input Pullup (savety precaution)
    pinMode(button_left, INPUT_PULLUP);
    pinMode(button_middle, INPUT_PULLUP);
    pinMode(button_right, INPUT_PULLUP);
    
    // LEDs to Outputs
    pinMode(led_dual_red, OUTPUT);
    pinMode(led_dual_green, OUTPUT);
    pinMode(led_yellow_pin, OUTPUT);

    // Buttons to Input Pullup (savety precaution)
    pinMode(encoder_clk, INPUT_PULLUP);
    pinMode(encoder_dt, INPUT_PULLUP);
    pinMode(encoder_sw, INPUT_PULLUP);  
}