using namespace std;
#include <Arduino.h>
#include <Wifi.h>
#include <PubSubClient.h>
#include "SerialCom.h"
#include "Config.h"

#define REPORT_DELAY 30 //seconds
#define lmillis() ((long)millis())

// WIFI
WiFiClient espClient;
PubSubClient client(espClient);

const char* client_id = "fe514e7d-a92d-4661-9723-a7a5d99ebb52";
const char* ssid = "htl-schueler";
const char ssid_arr[] = "htl-schueler";

const char* wifikey = "20neuesWLAN17";
const char wifikey_arr[] = "20neuesWLAN17";
const char* topic = "temp";
const char* srvIp = "172.17.243.87";

const char* username = "SenseOfWellbeing";
const char* password = "admin01";

//char airQual[50];
//string airQual_str ="";

SensorState state;
long nextReport = 0;

void setupWifi(){
  delay(10);
  Serial.println("Connecting to:");
  Serial.print(ssid);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println(".");
  }

  Serial.println("WiFi connected");
  Serial.println("IP Adress: ");
  Serial.print(WiFi.localIP());
}

void setup() {
  pinMode(13,INPUT);
  Serial.begin(115200);
  
  SerialCom::setup();

  setupWifi();
  client.setServer(srvIp, 1883);
  client.connect(client_id, ssid_arr, wifikey_arr);

  nextReport = lmillis() + REPORT_DELAY * 1000;
}

void loop() {
  SerialCom::handleUart(state);
  if(lmillis() - nextReport >= 0){
      nextReport = lmillis() + REPORT_DELAY; //* 1000;
        delay(1000);
      if(state.valid){
        Serial.println(state.avgPM25);
        //String(state.avgPM25).toCharArray(airQual, String(state.avgPM25).length()+1);
        //client.publish(topic, airQual);
        client.publish(topic, state.avgPM25, String(state.avgPM25).length()); 
        // client.publish(topic, state.avgPM25);
        // client.publish()
      }
      else{
        Serial.println("---");
        Serial.println(nextReport + " " + lmillis());
      }
  }
}