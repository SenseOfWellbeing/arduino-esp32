using namespace std;
#include <Arduino.h>

#include "SSD1306.h"
#include "SerialCom.h"
#include <Wire.h>
#include "Config.h"

// Is this necerssary?
#define OLED_WIDTH 128
#define OLED_HEIGHT 32
#define OLED_PIN_RESET 4
#define OLED_ADRESS 0x78

#define REPORT_DELAY 30 //seconds
#define lmillis() ((long)millis())

// WIFI
const char* WIFI_SSID = "htl-schueler";
const char* WIFI_PASSWORD = "20neuesWLAN17";

SensorState state;
long nextReport = 0;

void setup() {
  pinMode(13,INPUT);
  Serial.begin(115200);
  
  SerialCom::setup();
  nextReport = lmillis() + REPORT_DELAY * 1000;
}

void loop() {
  SerialCom::handleUart(state);
  if(lmillis() - nextReport >= 0){
      nextReport = lmillis() + REPORT_DELAY; //* 1000;
        delay(1000);
      if(state.valid){
        Serial.println(state.avgPM25);
      }
      else{
        Serial.println("---");
        Serial.println(nextReport + " " + lmillis());
      }
  }
}