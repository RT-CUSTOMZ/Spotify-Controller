#include "encoder-hal.h"
#include <Arduino.h>
#include "pinconfig.h"
#include "led-hal.h"

static int16_t inputDelta = 0;             // Counts up or down depending which way the encoder is turned
static bool printFlag = false;             // Flag to indicate that the value of inputDelta should be printed

void readEncoder() {
    static uint8_t state = 0;
    bool CLKstate = digitalRead(encoder_clk);
    bool DTstate = digitalRead(encoder_dt);

    switch (state) {
        case 0:                         // Idle state, encoder not turning
            if (!CLKstate){             // Turn clockwise and CLK goes low first
                ledOff(led_dual_green);
                ledOff(led_dual_green);
                ledOff(led_yellow_pin);
                state = 1;
            } else if (!DTstate) {      // Turn anticlockwise and DT goes low first
                ledOn(led_dual_green);
                ledOff(led_dual_green);
                ledOff(led_yellow_pin);
                state = 4;
            }
            break;
        // Clockwise rotation
        case 1:                     
            if (!DTstate) {             // Continue clockwise and DT will go low after CLK
                ledOff(led_dual_red);
                ledOn(led_dual_green);
                ledOff(led_yellow_pin);
                state = 2;
            } 
            break;
        case 2:
            if (CLKstate) {             // Turn further and CLK will go high first
                ledOn(led_dual_red);
                ledOn(led_dual_green);
                ledOff(led_yellow_pin);
                state = 3;
            }
            break;
        case 3:
            if (CLKstate && DTstate) {  // Both CLK and DT now high as the encoder completes one step clockwise
                ledOff(led_dual_red);
                ledOff(led_dual_green);
                ledOn(led_yellow_pin);
                state = 0;
                ++inputDelta;
                printFlag = true;
            }
            break;
        // Anticlockwise rotation
        case 4:                         // As for clockwise but with CLK and DT reversed
            if (!CLKstate) {
                ledOn(led_dual_red);
                ledOff(led_dual_green);
                ledOn(led_yellow_pin);
                state = 5;
            }
            break;
        case 5:
            if (DTstate) {
                ledOff(led_dual_red);
                ledOn(led_dual_green);
                ledOn(led_yellow_pin);
                state = 6;
            }
            break;
        case 6:
            if (CLKstate && DTstate) {
                ledOn(led_dual_red);
                ledOn(led_dual_green);
                ledOn(led_yellow_pin);
                state = 0;
                --inputDelta;
                printFlag = true;
            }
            break; 
    }
}

void printDelta() {
    if (printFlag) {
        printFlag = false;
        Serial.println(inputDelta);
    }
}