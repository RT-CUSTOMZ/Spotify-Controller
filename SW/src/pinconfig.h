#pragma once
#include "Arduino.h"
/**************************************
    Do not change anything in this File
**************************************/

//Single Red LED
const uint8_t led_yellow_pin = 2; 

//Tri-Color LED
const uint8_t led_dual_red = 0;
const uint8_t led_dual_green = 1;

//User Buttons
const uint8_t button_left = 8;
const uint8_t button_middle = 20;
const uint8_t button_right = 21;


//Display Pins
const uint8_t display_sda = 7;
const uint8_t display_scl = 6;

//USB Pins
const uint8_t usb_dn = 18;
const uint8_t usb_dp = 19;

//Encoder Pins
const uint8_t encoder_clk = 3;
const uint8_t encoder_dt = 4;
const uint8_t encoder_sw = 5;

void InitPins();