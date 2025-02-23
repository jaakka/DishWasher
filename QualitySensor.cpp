#include "QualitySensor.h"

QualitySensor::QualitySensor() {
    sensorValue = 0;
}

void QualitySensor::begin() {

}

void QualitySensor::loop() {

}

float QualitySensor::getSensorValue() {
    return sensorValue;
}