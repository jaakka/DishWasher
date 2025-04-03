#include "QualitySensor.h"

QualitySensor::QualitySensor() {
    sensorValue = 0;
}

void QualitySensor::begin() {
    pinMode(QUALITITY_SENSOR_PIN, INPUT);
}

void QualitySensor::loop() {
    sensorValue = analogRead(QUALITITY_SENSOR_PIN);
    sensorValue = map(sensorValue, 0, 630, 0, 100);
}

float QualitySensor::getSensorValue() {
    return sensorValue;
}

