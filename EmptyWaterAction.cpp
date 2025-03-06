#include "EmptyWaterAction.h"

void EmptyWaterAction::execute() {

    if(!actionStarted) {
        if(sensorHandler->waterLevelMax())
        {
            relayHandler->startEmptyPump();
            startTime = millis();
            actionStarted = true;

            if(ENABLE_ACTIONS_DEBUG) {
                Serial.println("Empty water - pump started");
            }
        }

        if(sensorHandler->waterLevelNotMax()) {
            errorCode = ERROR_WATER_LEVEL_TOO_LOW_FOR_EMPTY;
            error = true;
            if(ENABLE_ACTIONS_DEBUG) {
                Serial.println("Empty water - error: water level not max");
            }
        }
    }

    if(millis() - startTime > (unsigned long)WATER_EMPTY_PUMP_TIME * 1000) {
        relayHandler->stopEmptyPump();

        if(ENABLE_ACTIONS_DEBUG) {
            Serial.println("Empty water - pump stopped");
        }

        if(sensorHandler->waterLevelMax()) {
            errorCode = ERROR_WATER_EMPTY_TIME_LIMIT_REACHED;
            error = true;
            if(ENABLE_ACTIONS_DEBUG) {
                Serial.println("Empty water - error: water level still max");
            }
        }

        if(sensorHandler->waterLevelNotMax()) {
            actionFinished = true;
            if(ENABLE_ACTIONS_DEBUG) {
                Serial.println("Empty water - finished");
            }
        }
    }
}

ActionState EmptyWaterAction::status() {
    if(error) {
        return ActionState::ERROR;
    } else if(actionFinished) {
        return ActionState::FINISHED;
    } else if(actionStarted) {
        return ActionState::IN_PROGRESS;
    } else {
        return ActionState::NOT_STARTED;
    }
}

int EmptyWaterAction::getRemainingDuration() { 
  return (WATER_EMPTY_PUMP_TIME * 1000 - (millis() - startTime)) / 1000;
}

int EmptyWaterAction::getDuration() {
  return WATER_EMPTY_PUMP_TIME;  
}

int EmptyWaterAction::getErrorCode() {
  return errorCode;
}

EmptyWaterAction::EmptyWaterAction(SafetyHandler* safetyHandler, RelayHandler* relayHandler, SensorHandler* sensorHandler) {
  this->relayHandler = relayHandler;
  this->safetyHandler = safetyHandler;
  this->sensorHandler = sensorHandler;
  actionStarted = false;
  actionFinished = false;
  waterIsMaxOnStart = false;
  error = false;
}