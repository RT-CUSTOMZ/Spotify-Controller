#include "display-hal.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "pinconfig.h"

#include <Wire.h>
#include <U8g2lib.h>

TwoWire myWire = TwoWire(0); // 0 represents the primary I2C bus
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R2, /* clock=*/ display_scl, /* data=*/ display_sda, /* reset=*/ U8X8_PIN_NONE);

void InitDisplay() {
  u8g2.begin();

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvR14_tf);
  u8g2.drawUTF8(0, 20, "Westfälische");
  u8g2.drawUTF8(0, 40, "Hochschule");
  // u8g2.sendF("caaaaaac", 0x027, 0, 3, 0, 7, 0, 255, 0x2f);
  u8g2.sendBuffer();
}


char title[] = "Langer Titel, der gescrollt wird";
char artist[] = "Künstler";

void DisplayLoop() {

// Scroll-Titel
  testscrolltext(title, artist);
}


void testscrolltext(char* text1, char* text2, uint8_t positionY1, uint8_t positionY2) {
  u8g2.clearBuffer();
  u8g2.drawUTF8(0, 20, text1);
  u8g2.drawUTF8(16, 20, text2);
  u8g2.sendBuffer();
}
