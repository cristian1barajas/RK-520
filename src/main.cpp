#include <Arduino.h>
#include <Rika520.h>

// Global variables
Rika520 sensor;
unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
    Serial.begin(9600);
}

void loop() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        sensor.writeRika();
        
        SensorData data = sensor.readSense();
        if(data.isValid) {
            Serial.print("Temperature: "); Serial.print(data.temperature, 1); Serial.println(" C");
            Serial.print("Moisture: "); Serial.print(data.moisture, 1); Serial.println(" %");
            Serial.print("EC: "); Serial.print(data.ec, 3); Serial.println(" mS/cm");
            Serial.println("-----");
        }
    }
}
