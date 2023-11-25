#pragma once

#define PIN_WIRE_SDA         (7u)
#define PIN_WIRE_SCL         (6u)

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x78 ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

void init_display();
void display_loop();