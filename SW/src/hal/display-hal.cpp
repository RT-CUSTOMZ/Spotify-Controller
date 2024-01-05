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
  u8g2.setFont(u8g2_font_helvR14_tf); // Beispielhaft: Wähle eine Schriftart, die Umlaute unterstützt
  // u8g2.drawUTF8(0, 20, "Umlaute: ÄÖÜäöü\t");
  u8g2.sendF("caaaaaac", 0x027, 0, 3, 0, 7, 0, 255, 0x2f);
    // u8g2.print("ä");
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

// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &myWire, OLED_RESET);



// void InitDisplay(){
//     myWire.begin(display_sda, display_scl);
//     // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
//     if(!display.begin(SSD1306_SWITCHCAPVCC , SCREEN_ADDRESS)) {
//         Serial.println(F("SSD1306 allocation failed"));
//         for(;;);
//     }

//   display.setRotation(2);
//   display.display();
//   delay(2000); // Pause for 2 seconds

//   // Clear the buffer
//   display.clearDisplay();

//   // Draw a single pixel in white
//   display.drawPixel(10, 10, SSD1306_WHITE);
//   display.setTextColor(SSD1306_WHITE);
//   display.setFont(ArialMT_Plain_10);

//   // Show the display buffer on the screen. You MUST call display() after
//   // drawing commands to make them visible on screen!
//   display.display();
//   delay(2000);

//   display.print("Umlaute: ä ö ü");
//   delay(1000);

//   char Song[] = "Westfälische Hochschule";

//   char Interpreter[] = "Interpreter";
//   testscrolltext(Song, Interpreter);    // Draw scrolling text
// }

// void DisplayLoop(){  
//   // const char textToScroll[] = "This is a 30-char array!";
//   // scrollText(textToScroll);
//   yield();
//   display.display();
// }



// void testdrawbitmap(void) {
//   display.clearDisplay();

//   display.drawBitmap(
//     (display.width()  - LOGO_WIDTH ) / 2,
//     (display.height() - LOGO_HEIGHT) / 2,
//     logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
//   display.display();
//   delay(1000);
// }

