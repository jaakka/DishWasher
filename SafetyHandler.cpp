#include "SafetyHandler.h"
#include "SensorHandler.h"

SafetyHandler::SafetyHandler(SensorHandler* sensorHandler) {
    this->sensorHandler = sensorHandler;
    state = SafetyState::OK;
}

void SafetyHandler::begin() {
    // Nothing to do
}

void SafetyHandler::loop() {
    if(checkOverheat() || checkFlood()) {
        state = SafetyState::ERROR;
    } else if(checkDoor()) {
        state = SafetyState::PAUSE;
    } else {
        state = SafetyState::OK;
    }
}

SafetyState SafetyHandler::getState() {
    return state;
}

bool SafetyHandler::checkOverheat() {
    if(sensorHandler->overheating()) {
        return true;
    }
    return false;
}

bool SafetyHandler::checkFlood() {
    if(sensorHandler->floodDetected()) {
        return true;
    }
    return false;
}

bool SafetyHandler::checkDoor() {
    if(sensorHandler->doorIsOpen()) {
        return true;
    }
    return false;
}