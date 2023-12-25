#include "encoder-hal.h"
#include <Arduino.h>
#include "pinconfig.h"
#include "led-hal.h"
#include <SpotifyESP32.h>

static int16_t StepDelta = 0;             // Counts up or down depending which way the encoder is turned
static bool outputCount = false;             // Flag to indicate that the value of inputDelta should be printed
static bool positive = false;             // step was positive
static bool negative = false;             // step was negative
static uint16_t last_delta = StepDelta;   //used to determine the next volume


extern Spotify sp;

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
                positive = true; 
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
                negative = true; 
            }
            break; 
    }
}


void encoderFunction(){
    response getDevices {sp.available_devices()};
    bool supports_volume = false;
    uint8_t volume = 255;

    int16_t difference = last_delta - StepDelta;

    if((getDevices.status_code>=200)&&(getDevices.status_code<=299)){

        DynamicJsonDocument doc(2000);
        deserializeJson(doc,getDevices.reply);
        JsonArray devices = doc["devices"].as<JsonArray>();

        for (JsonVariant device : devices) {
            JsonObject deviceObj = device.as<JsonObject>();

            if (deviceObj["is_active"].as<bool>()) {
                supports_volume = deviceObj["supports_volume"].as<bool>();
                volume = deviceObj["volume_percent"].as<uint8_t>();
                break;
            }
        }  
    }

    if(supports_volume){
        
        const uint8_t volume_step = 10; 

        uint8_t total_volume = volume_step*difference;

        if(negative == true){
            if((volume-total_volume)<0){
                sp.set_volume(0);
            }
            else{
                sp.set_volume(volume - total_volume);
            }
            negative = false;
        } else if(positive == true){
            if((volume+total_volume)>100){
                sp.set_volume(100);
            } else {
                sp.set_volume(volume + total_volume);
            }
            positive = false;
        }
    
    last_delta = StepDelta;  
    }
}

void printDelta() {
    if (outputCount) {
        outputCount = false;
        encoderFunction();
        Serial.println(StepDelta);
    }
}