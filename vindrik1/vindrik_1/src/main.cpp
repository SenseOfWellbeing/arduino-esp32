using namespace std;
#include <Arduino.h>

#include "SSD1306.h"
#include "SerialCom.h"
#include <Wire.h>
#include "Config.h"

// -------------
#include <WiFi.h>
#include <PubSubClient.h>
WiFiClient espClient;
PubSubClient client(espClient);

#pragma region // Const for Mqtt

const char* client_id = "fe514e7d-a92d-4661-9723-a7a5d99ebb52";
const char ssid[] = "htl-schueler";
const char* wifikey = "20neuesWLAN17";
const char* topic = "temp";
const char* message = "halloleute"; 

const char* username = "SenseOfWellbeing";
const char* password = "admin01";

#pragma endregion

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
  Serial.begin(115200);
  SerialCom::setup();
  nextReport = lmillis() + REPORT_DELAY * 1000;

  //

  setup_wifi();
    
    client.setServer("172.17.243.87",1883);
    client.connect (client_id, ssid, wifikey);


}

void setup_wifi() 
{
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  SerialCom::handleUart(state);
  // if(lmillis() - nextReport >= 0){
      // nextReport = lmillis() + REPORT_DELAY; //* 1000;
        delay(100);
      // if(state.valid){
        Serial.println("Wert: " + state.avgPM25);
        client.publish(topic,message);
      // }
      // else{
        // Serial.println("---");
        // Serial.println(nextReport + " " + lmillis());
      // }
  // }
}