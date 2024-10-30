#include "Rika520.h"

const char Rika520::hexa52002[8] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x03, 0x05, 0xCB};

Rika520::Rika520() {
    memset(dataSensor, 0, nbytes_sensor);
}

void Rika520::writeRika() {
    for (byte s = 0; s < 8; s++) {
        Serial.write(hexa52002[s]);
    }
}

SensorData Rika520::readSense() {
    SensorData result = {0, 0, 0, false};  // Default invalid data
    while (Serial.available() > 0) {
        char inputChar = (char)Serial.read();
        dataSensor[indexData] = inputChar;
        indexData++;

        if (indexData == nbytes_sensor) {
            if (dataSensor[0] == 0x01 && dataSensor[1] == 0x03) {
                result = convertData(dataSensor);
                result.isValid = true;  // Indicate that the data is valid
            }
            memset(dataSensor, 0, nbytes_sensor);
            indexData = 0;
        }
    }
    return result;
}

SensorData Rika520::convertData(byte data[]) {
    SensorData result;
    result.temperature = (float)((data[3] << 8) | data[4]) / 10.0;
    result.moisture = (float)((data[5] << 8) | data[6]) / 10.0;
    result.ec = (float)((data[7] << 8) | data[8]) / 1000.0;
    //result.isValid = false;  // Default value
    return result;
}