using namespace std;
#include <Arduino.h>
#include <Wifi.h>
#include <PubSubClient.h> // Mqtt-Bibliothek
#include "SerialCom.h"
#include "Config.h"
#include <ESP32Ping.h>

// Problem:  
// Es kommt keine Nachricht beim Broker an. -> Verliert Signal nach einiger Zeit.
// Es muss an WLAN liegen -> manchmal geht es, nach gewissen Zeit verliert ESP32 immer WLAN-Signal
// Aber auch bei WLAN-Signal kommt keine Nachricht an.
// WLAN und/oder Mqtt-Client verliert Signal.

#define REPORT_DELAY 30 //seconds
#define lmillis() ((long)millis())

// Mqtt-Client via WiFi erstellen
WiFiClient espClient;
PubSubClient client(espClient);

const char* client_id = "PublisherId"; // kann man sich aussuchen, nur sollte jeder Publisher eigene haben
// const char* client_id = "fe514e7d-a92d-4661-9723-a7a5d99ebb52"; // alte Id

const char* ssid = "htl-schueler";
const char* wifikey = "20neuesWLAN17";

const char* topic = "airQuality"; // Mqtt-Topic ... für openHab
const char* srvIp = "172.17.243.87"; // ip-Adresse von PC, auf dem openHab läuft

// Login-Daten für openHab
const char* username = "SenseOfWellbeing";
const char* password = "admin01";

int WifiNotConnectedCounter;

SensorState state;
long nextReport = 0;

void pingSimonsLaptop() // Funktion zum pingen von Simons Laptop ... zum testen ob WiFi-Verbindung besteht
{
  Serial.print("Pinging ip ");
  Serial.println("172.17.243.85");

  if(Ping.ping("172.17.243.85")) {
    Serial.println("Success!!");
  } else {
    Serial.println("Error :(");
  }
}

void setupWifi(){
  delay(10);
  Serial.println("Connecting to: ");
  Serial.print(ssid);

  WiFi.begin(ssid, wifikey); // Wifi verbinden

  pingSimonsLaptop();

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println(".");
    WifiNotConnectedCounter = WifiNotConnectedCounter + 1;

    if(WifiNotConnectedCounter = 10) // WiFi reconnect ... wenn verbinden zu lange dauert
    {
      WifiNotConnectedCounter = 0;
      setupWifi();
    }
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

  pingSimonsLaptop();
  
  client.connect(client_id, username, password);
  while(client.connected() == false)
  {
    delay(500);
    Serial.println("Client is connecting ..."); 
  }
  
  nextReport = lmillis() + REPORT_DELAY * 1000;
}

void loop() {
  SerialCom::handleUart(state);
  if(lmillis() - nextReport >= 0){
      nextReport = lmillis() + REPORT_DELAY; //* 1000;
        delay(1000);

      if(state.valid){
        
        Serial.println(client.state());
        Serial.println(state.avgPM25);
        client.publish(topic, "37");

        pingSimonsLaptop(); // Schauen, ob Esp32 noch Netz-Zugang hat

        // Vorbereitung, um Wert als String zu übergeben. Auskommentiert, da zurzeit nicht einmal fixer Wert gesendet werden kann.

        //client.publish(topic, state.avgPM25, String(state.avgPM25).length()); 
        // client.publish(topic, state.avgPM25);

      }
      else{
        Serial.println("---");
        Serial.println(nextReport + " " + lmillis());
      }
  }
}

// Kepplinger Stephan und Simon Gruber