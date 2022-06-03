#include <SoftwareSerial.h>

#include <SSD1306.h>
// #include <splash.h>
#include <SoftwareSerial.h>
#include "Types.h"

namespace SerialCom {
    // constexpr static const uint8_t PIN_UART_RX = 40; // GPIO 3
    constexpr static const uint8_t PIN_UART_RX = 13;
    constexpr static const uint8_t PIN_UART_TX = 15; // UNUSED

    uint8_t serialRxBuf[255];
    uint8_t rxBufIdx = 0;

    void setup() {
        pinMode(PIN_UART_RX, INPUT);
        pinMode(PIN_UART_TX, OUTPUT);
        Serial2.begin(9600, SERIAL_8N1, PIN_UART_RX, PIN_UART_TX);
    }

    void clearRxBuf() {
        // Clear everything for the next message
        memset(serialRxBuf, 0, sizeof(serialRxBuf));
        rxBufIdx = 0;
    }

    void parseState(SensorState& state) {
        const uint16_t pm25 = (serialRxBuf[5] << 8) | serialRxBuf[6];

        state.measurements[state.measurementIdx] = pm25;
        state.measurementIdx = (state.measurementIdx + 1) % 5;
        Serial.println(state.measurements[0] + " measurement 0");
        if (state.measurementIdx == 0) {
            float avgPM25 = 0.0f;
            for (uint8_t i = 0; i < 5; ++i) {
                avgPM25 += state.measurements[i] / 5.0f;
            }
            state.avgPM25 = avgPM25;
            state.valid = true;
        }
        clearRxBuf();
    }

    bool isValidHeader() {
        bool headerValid = serialRxBuf[0] == 0x16 && serialRxBuf[1] == 0x11 && serialRxBuf[2] == 0x0B;
        return headerValid;
    }

    bool isValidChecksum() {
        uint8_t checksum = 0;
        for (uint8_t i = 0; i < 20; i++) {
            checksum += serialRxBuf[i];
        }
        return checksum == 0;
    }

    void handleUart(SensorState& state) {
        if (!Serial2.available()) {
            return;
        }
        while (Serial2.available()) {
            serialRxBuf[rxBufIdx++] = Serial2.read();
            // Serial.println(serialRxBuf[rxBufIdx]);
            delay(15);
            if (rxBufIdx >= 64) {
                clearRxBuf();
            }
        }
        if (isValidHeader() && isValidChecksum()) {
            parseState(state);
        }
        else {
            clearRxBuf();
        }
    }
}
