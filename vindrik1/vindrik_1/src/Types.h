#pragma once

struct particleSensorState_t {
    // uint16_t avgPM25 = 0;
    __uint128_t avgPM25 = 0;
    // uint16_t measurements[5] = {0, 0, 0, 0, 0};
    __uint128_t measurements[5] = {0, 0, 0, 0, 0};
    //uint8_t measurementIdx = 0;
    __uint128_t measurementIdx = 0;
    //boolean valid = false;
    bool valid = false;
};