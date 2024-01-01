#pragma once
#include <Arduino.h> 
#include <SpotifyESP32.h>
void printDelta();
void readEncoder();
uint8_t getCurrentVolumeFromSpotify(response get_devices);
void calculateAndSetNewSpotifyVolume(uint16_t current_volume);

/*
Called on Interrupt on Pin encoder_dt and sets a changed flag for the button.
*/
void OnEncoderDtChange();

/*
Called on Interrupt on Pin encoder_clk and sets a changed flag for the button.
*/
void OnEncoderClkChange();
