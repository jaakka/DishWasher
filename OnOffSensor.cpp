#include "OnOffSensor.h"
#include <Arduino.h>
#include "Config.h"

OnOffSensor::OnOffSensor(int sensorPin) {
    this->sensorPin = sensorPin;
    sensorState = false;
    pinMode(sensorPin, INPUT);
}

void OnOffSensor::loop() {;
    if (analogRead(sensorPin) > BOOL_SENSORS_MIN_DETECT_VALUE) {
        sensorState = true;
    } else {
        sensorState = false;
    }
}