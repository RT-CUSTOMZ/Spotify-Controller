#pragma once
#include <Arduino.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32





#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16


void testscrolltext(char* text1, char* text2, uint8_t positionY1=0 , uint8_t positionY2 = 60);
void testdrawbitmap();

void InitDisplay();
void DisplayLoop();