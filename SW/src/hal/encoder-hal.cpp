#include "encoder-hal.h"
#include <Arduino.h>
#include "pinconfig.h"
#include "led-hal.h"

static int16_t StepDelta = 0;             // Counts up or down depending which way the encoder is turned
static bool outputCount = false;             // Flag to indicate that the value of inputDelta should be printed

enum EncoderState {
  InitState,
  ClockwiseRotationA,  
  ClockwiseRotationB,  
  ClockwiseRotationC,  
  CounterClockwiseRotationA,
  CounterClockwiseRotationB,
  CounterClockwiseRotationC,
};

void readEncoder() {
    static EncoderState state = EncoderState::InitState;
    bool CLK = digitalRead(encoder_clk);
    bool DT = digitalRead(encoder_dt);

    switch (state) {
        case EncoderState::InitState:                         // Idle state, encoder not turning
            if (!CLK){                  // Turn clockwise and CLK goes low first
                state = EncoderState::ClockwiseRotationA;
            } else if (!DT) {           // Turn anticlockwise and DT goes low first
                state = EncoderState::CounterClockwiseRotationA;
            }
            break;
        
        // Clockwise rotation
        case EncoderState::ClockwiseRotationA:                     
            if (!DT) {                  // Continue clockwise and DT will go low after CLK
                state = EncoderState::ClockwiseRotationB;
            } 
            break;
        case EncoderState::ClockwiseRotationB:
            if (CLK) {                  // Turn further and CLK will go high first
                state = EncoderState::ClockwiseRotationC;
            }
            break;
        case EncoderState::ClockwiseRotationC:
            if (CLK && DT) {            // Both CLK and DT now high as the encoder completes one step clockwise
                state = EncoderState::InitState;
                ++StepDelta;
                outputCount = true;
            }
            break;
        // Anticlockwise rotation
        case EncoderState::CounterClockwiseRotationA:                         // As for clockwise but with CLK and DT reversed
            if (!CLK) {
                state = EncoderState::CounterClockwiseRotationB;
            }
            break;
        case EncoderState::CounterClockwiseRotationB:
            if (DT) {
                state = EncoderState::CounterClockwiseRotationC;
            }
            break;
        case EncoderState::CounterClockwiseRotationC:
            if (CLK && DT) {
                state = EncoderState::InitState;
                --StepDelta;
                outputCount = true;
            }
            break; 
    }
}

void printDelta() {
    if (outputCount) {
        outputCount = false;
        Serial.println(StepDelta);
    }
}