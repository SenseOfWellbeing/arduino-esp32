//#include "ssd1306.h"
#include "SerialCom.h"
#include "Config.h"
#include "Types.h"

particleSensorState_t state;
uint32_t statusPublishPreviousMillis = 0;
const uint16_t statusPublishInterval = 30000; // 30 seconds = 30000 milliseconds


void setup()
{
    //ssd1306_setFixedFont(ssd1306xled_font6x8);
    //sh1106_128x64_i2c_init();

    //ssd1306_clearscreen();

     Serial.begin(115200);
    SerialCom::setup();

    Config::load();

    Serial.println("\n");
    Serial.println("Hello from esp32-vindriktning-particle-sensor");
    /*Serial.print("Core Version: %s\n", ESP.getCoreVersion().c_str());
    Serial.print("Cores: %s\n", ESP.getChipCores().c_str());
    Serial.print("Boot Version: %u\n", ESP.getBootVersion());
    Serial.print("Boot Mode: %u\n", ESP.getBootMode());
    Serial.print("CPU Frequency: %u MHz\n", ESP.getCpuFreqMHz());
    Serial.print("Reset reason: %s\n", ESP.getResetReason().c_str());*/

    Serial.println("-- Current GPIO Configuration --");
    Serial.println("PIN_UART_RX: %d\n");
    Serial.println(SerialCom::PIN_UART_RX);


}

void loop()
{
    //delay(1000);
    //ssd1306_clearScreen();
    SerialCom::handleUart(state);
    const uint32_t currentMillis = millis();
    if (currentMillis - statusPublishPreviousMillis >= statusPublishInterval) {
        statusPublishPreviousMillis = currentMillis;

        if (state.valid) {
            Serial.print("Publish state\n");
            publishState();
        }
    }


}
void publishState() {
    /*DynamicJsonDocument wifiJson(192);
    DynamicJsonDocument stateJson(604);
    char payload[256];

    wifiJson["ssid"] = WiFi.SSID();
    wifiJson["ip"] = WiFi.localIP().toString();
    wifiJson["rssi"] = WiFi.RSSI();

    stateJson["pm25"] = state.avgPM25;

    stateJson["wifi"] = wifiJson.as<JsonObject>();

    serializeJson(stateJson, payload);
    mqttClient.publish(&MQTT_TOPIC_STATE[0], &payload[0], true);
*/}
