#include "OnOffSensor.h"
#include <Arduino.h>
#include "Config.h"

OnOffSensor::OnOffSensor(int sensorPin) {
    this->sensorPin = sensorPin;
    pinMode(sensorPin, INPUT);
}

void OnOffSensor::loop() {
    sensorValue = analogRead(sensorPin);
}

bool OnOffSensor::getSensorState() {
    return sensorValue > BOOL_SENSORS_MIN_DETECT_VALUE;
}

