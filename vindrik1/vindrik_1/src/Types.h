struct SensorState
{
    uint16_t avgPM25 = 0;
    uint16_t measurements[5] = {0, 0, 0, 0, 0};
    uint16_t measurementIdx = 0;
    boolean valid = false;
};
