#include <Arduino.h>
// #include <WiFi.h>
// #include <PubSubClient.h>
#include <Wire.h>
#include <iostream>
#include <cstring>

// WiFiClient espClient;
// PubSubClient client(espClient);

const char* client_id = "fe514e7d-a92d-4661-9723-a7a5d99ebb52";
const char* ssid = "htl-schueler";
const char ssid_arr[] = "htl-schueler";

const char* wifikey = "20neuesWLAN17";
const char wifikey_arr[] = "20neuesWLAN17";
const char* topic = "temp";
// const char* message = "42"; 
uint8_t *payload;
unsigned int plength = 2;

const char* username = "SenseOfWellbeing";
const char* password = "admin01";

// void setup_wifi(){
//   delay(10);
//   Serial.println("Connecting to:");
//   Serial.println(ssid);
  
//   WiFi.begin(ssid, password);

//   while(WiFi.status() != WL_CONNECTED){
//     delay(500);
//     Serial.print(".");
//   }

//   Serial.println("WiFi connected");
//   Serial.println("IP Adress: ");
//   Serial.println(WiFi.localIP());
// }

void setup() {
//   setup_wifi();
//   client.setServer("172.17.243.87", 1883);
//   client.connect(client_id,ssid_arr, wifikey_arr);
  Serial1.println(" 1 Test Setup ------------------------");
  Serial2.println(" 2 Test Setup ------------------------");
  Serial.println(" Serial Test Setup ------------------------");
}

void loop() {
  // client.publish(topic, payload, plength);
  // if(client.publish(topic, payload, plength)){
  //   // Serial.println(payload);
  // }
  delay(10);
  // client.loop();
  delay(1000);
  Serial1.println("Abc Abc ");
}