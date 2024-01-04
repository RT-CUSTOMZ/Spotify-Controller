#include "display-hal.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "pinconfig.h"

TwoWire myWire = TwoWire(0); // 0 represents the primary I2C bus
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &myWire, OLED_RESET);

static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };

void init_display(){
    digitalWrite(led_dual_green, HIGH);
    delay(100);

    Serial.println("OLED test");
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    myWire.begin(display_sda, display_scl);
    if(!display.begin(SSD1306_SWITCHCAPVCC , SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
    }
// Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.setRotation(2);
  display.display();
  delay(2000); // Pause for 2 seconds
  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(2000);
  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display(). These examples demonstrate both approaches...

  testdrawbitmap();    // Draw a small bitmap image

  // Invert and restore display, pausing in-between
  display.invertDisplay(true);
  delay(1000);
  display.invertDisplay(false);
  delay(1000);
  char Song[] = "Song";
  char Interpreter[] = "Interpreter";
  testscrolltext(Song, Interpreter);    // Draw scrolling text
}

void display_loop(){  
//   yield();
//   display.display();
}


void testscrolltext(char* text1, char* text2, uint8_t positionY1, uint8_t positionY2) {
  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(10, positionY1);
  display.println(F(text1));
//   display.display();      // Show initial text

//   display.setCursor(10, positionY2);
  display.println(F(text2));
  display.display();      // Show initial text

  delay(200);

  // Scroll in various directions, pausing in-between:
  display.startscrollright(0x00, 0x0F);
}

void testdrawbitmap(void) {
  display.clearDisplay();

  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(1000);
}
