#include "encoder-hal.h"
#include <Arduino.h>
#include "pinconfig.h"
#include "led-hal.h"
#include "button-hal.h"
#include <SpotifyESP32.h>

static int16_t new_step_value = 0;             // Counts up or down depending which way the encoder is turned
static bool outputCount = false;             // Flag to indicate that the value of inputDelta should be printed
static uint16_t last_step_value = new_step_value;   //used to determine the next volume
static uint8_t encoder_last_changed = 0;

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

Button encoderDt;
Button encoderClk;




void EncoderLoop() {
    static EncoderState state = EncoderState::InitState;
    bool CLK = digitalRead(encoder_clk);
    bool DT = digitalRead(encoder_dt);

    switch (state) {
        case EncoderState::InitState:                         // Idle state, encoder not turning
            if (!CLK){                  // Turn clockwise and CLK goes low first
                state = EncoderState::ClockwiseRotationA;
            } else if (!DT) {           // Turn anticlockwise and DT goes low first
                state = EncoderState::CounterClockwiseRotationA;
            } else {
                 if(outputCount == true){
                    uint16_t encoder_current_change = millis();
                    if((encoder_current_change - encoder_last_changed) >= 700){
                        response getDevices {sp.available_devices()};
                        uint8_t volume = getCurrentVolumeFromSpotify(getDevices);
                        calculateAndSetNewSpotifyVolume(volume);
                        Serial.println(new_step_value);
                        outputCount = false;
                    }
                }
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
                new_step_value++;
                outputCount = true;
                Serial.printf("+");
                encoder_last_changed = millis();
                state = EncoderState::InitState;
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
                new_step_value--;
                outputCount = true;
                Serial.printf("-");
                encoder_last_changed = millis();
                state = EncoderState::InitState;
            }
            break; 
        
    }
   

}



uint8_t getCurrentVolumeFromSpotify(response get_devices){
    bool supports_volume = false;
    uint8_t volume = 0;

    if((get_devices.status_code>=200)&&(get_devices.status_code<=299)){

        DynamicJsonDocument doc(2000);
        deserializeJson(doc,get_devices.reply);
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

    if(false == supports_volume){
        return UINT8_MAX;
    } else {
        return volume;
    }
}

void calculateAndSetNewSpotifyVolume(uint8_t current_volume){

    int16_t step_difference = new_step_value - last_step_value; //can be positive and negative
    Serial.printf("Step difference: %d", step_difference);
    Serial.printf("Current volume: %d", current_volume);


    if(current_volume <= 100){
        const uint8_t volume_step_size = 10; //this is how much volume is added/substraceted on one rotation

        uint8_t new_volume_difference = volume_step_size*step_difference; // later add or substract this volume from the previous
        current_volume = current_volume + new_volume_difference;

        if(current_volume < 0){
            current_volume = 0;
        }else if(current_volume > 100){
            current_volume = 100;
        }
        
        Serial.println(current_volume);
        sp.set_volume(current_volume);
        last_step_value = new_step_value;  
    }
}


