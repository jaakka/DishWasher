#include "WashAction.h"

WashAction::WashAction(SafetyHandler* safetyHandler, RelayHandler* relayHandler, SensorHandler* sensorHandler, int washTimeInSeconds) {
    this->safetyHandler = safetyHandler;
    this->relayHandler = relayHandler;
    this->sensorHandler = sensorHandler;
    this->washTimeInSeconds = washTimeInSeconds;
    this->actionStarted = false;
    this->error = false;
    this->actionFinished = false;
}

void WashAction::execute() {
    if(!actionStarted && !actionFinished) {
      //Serial.print("Wash not started, ");
        if(sensorHandler->waterLevelMax()) {
            startTime = millis();
            actionStarted = true;
            relayHandler->startWashPump();
            //Serial.println("starting wash.");
            if(ENABLE_ACTIONS_DEBUG) {
                Serial.println("Washing started");
            }
        }

        if(sensorHandler->waterLevelNotMax()) {
            error = true;
            //Serial.println("water is too low.");
            if(ENABLE_ACTIONS_DEBUG) {
                Serial.println("Washing error - water level not max");
            }
        }
    } 
    
    if(actionStarted && !actionFinished) {
      //Serial.print("Wash is active, ");
        if(millis() - startTime > (unsigned long)washTimeInSeconds * 1000) {
          //Serial.print("Timelimit, ");
            relayHandler->stopWashPump();
            actionFinished = true;
            //Serial.println("Stopping");
            if(ENABLE_ACTIONS_DEBUG) {
                Serial.println("Washing finished");
            }
        }
    }
    //Serial.println();
}

ActionState WashAction::status() {
    if(error) {return ActionState::ERROR;}
    if(actionStarted) {
        if(actionFinished) {
            return ActionState::FINISHED;
        } else {
            return ActionState::IN_PROGRESS;
        }
    } else {
        return ActionState::NOT_STARTED;
    }
}

int WashAction::getRemainingDuration() {
    if(actionStarted) {
        return ((unsigned long)washTimeInSeconds * 1000 - (millis() - startTime)) / 1000;
    } else {
        return washTimeInSeconds;
    }
}

int WashAction::getDuration() {
    return washTimeInSeconds;
}

int WashAction::getErrorCode() {
    return ERROR_WATER_LEVEL_TOO_LOW_FOR_WASH;
    // TODO: Check water flow from water quality sensor 
}