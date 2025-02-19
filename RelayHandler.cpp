#include "RelayHandler.h"
#include "Wiring.h"
#include <Arduino.h>

void RelayHandler::begin() {
    pinMode(VALVE_RELAY_PIN, OUTPUT);
    pinMode(PUMPOUT_RELAY_PIN, OUTPUT);
    pinMode(PUMPWASH_RELAY_PIN, OUTPUT);
    pinMode(HEATER_RELAY_PIN, OUTPUT);
    pinMode(SOAPDOOR_RELAY_PIN, OUTPUT);
    pinMode(POWERCONTROL_RELAY_PIN, OUTPUT);
    digitalWrite(POWERCONTROL_RELAY_PIN, HIGH);
}  

void RelayHandler::mainPowerOff() {
    digitalWrite(POWERCONTROL_RELAY_PIN,LOW);
}