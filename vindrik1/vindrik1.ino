#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "SerialCom.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
SensorState state;
uint32_t next_report_millis = 0, t = 0;

void setup()
{
  SerialCom::setup();
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    while (true);
  }
  display.clearDisplay();
  display.display();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Air quality");
  display.display();
  delay(2000);
}

void loop()
{
  SerialCom::handleUart(state);
  t = millis();
  if (t > next_report_millis) {
    display.clearDisplay();
    display.setCursor(0, 0);
    next_report_millis = t + 10000;
    if (state.valid) {
      display.println(state.avgPM25);
    } else {
      display.println("?");
    }
    display.display();
  }
}
