#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor() : oneWire(DIGITAL_TEMP_SENSOR_PIN), dallasTemperature(&oneWire) {
    dallasTemperature.begin(); 
}

void TemperatureSensor::loop() {
    sensorValue = dallasTemperature.getTempCByIndex(0);
}

float TemperatureSensor::getSensorValue() {
    return sensorValue;
}