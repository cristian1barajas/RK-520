#ifndef RIKA520_H
#define RIKA520_H

#include <Arduino.h>

struct SensorData {
        float temperature;
        float moisture;
        float ec;
        bool isValid;
    };

class Rika520 {
private:
    static const char hexa52002[8];
    static const byte nbytes_sensor = 11;
    byte dataSensor[11];
    byte indexData = 0;

    SensorData convertData(byte data[]);  // Mover la declaración aquí

public:
    Rika520();
    void writeRika();
    SensorData readSense();
};

#endif