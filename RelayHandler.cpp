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
    digitalWrite(VALVE_RELAY_PIN, LOW);
    digitalWrite(PUMPOUT_RELAY_PIN, LOW);
    digitalWrite(PUMPWASH_RELAY_PIN, LOW);
    digitalWrite(HEATER_RELAY_PIN, LOW);
    digitalWrite(SOAPDOOR_RELAY_PIN, LOW);
}  

void RelayHandler::mainPowerOff() {
    digitalWrite(POWERCONTROL_RELAY_PIN,LOW);
}

void RelayHandler::openValve() {
    digitalWrite(VALVE_RELAY_PIN, HIGH);
}

void RelayHandler::closeValve() {
    digitalWrite(VALVE_RELAY_PIN, LOW);
}

void RelayHandler::openSoapDoor() {
    digitalWrite(SOAPDOOR_RELAY_PIN, HIGH);
}

void RelayHandler::closeSoapDoor() {
    digitalWrite(SOAPDOOR_RELAY_PIN, LOW);
}

void RelayHandler::heatWater() {
    digitalWrite(HEATER_RELAY_PIN, HIGH);
}

void RelayHandler::stopHeatingWater() {
    digitalWrite(HEATER_RELAY_PIN, LOW);
}