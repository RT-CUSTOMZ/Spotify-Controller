#pragma once
#include <Arduino.h> 
#include <SpotifyESP32.h>


void EncoderLoop();

uint8_t getCurrentVolumeFromSpotify(response get_devices);

void calculateAndSetNewSpotifyVolume(uint8_t current_volume);


