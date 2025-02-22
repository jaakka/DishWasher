#include "TemperatureSensor.h"
#include "Wiring.h"

TemperatureSensor::TemperatureSensor() : oneWire(DIGITAL_TEMP_SENSOR_PIN), dallasTemperature(&oneWire) {
    sensorValue = 0;
    dallasTemperature.begin(); 
}


void TemperatureSensor::loop() {
    sensorValue = dallasTemperature.getTempCByIndex(0);
}