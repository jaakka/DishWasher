#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor() : oneWire(PIN_TemperatureSensor), dallasTemperature(&oneWire) {
    dallasTemperature.begin(); 
}


void TemperatureSensor::loop() {

}