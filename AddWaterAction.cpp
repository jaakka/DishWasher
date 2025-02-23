#include "AddWaterAction.h"
#include "Config.h"
#include <Arduino.h>
#include "ErrorCodes.h"

void AddWaterAction::execute() {
  if(!isWaterAdded && !error) {
    if(sensorHandler->waterLevelNotMax())
    {
      if(!actionStarted) {
        actionStarted = true;
        actionStartTime = millis();
        if(ENABLE_ACTIONS_DEBUG) {
          Serial.println("Water add - valve open!");
        }
      }
      relayHandler->openValve();
    }
    if(sensorHandler->waterLevelMax())
    {
      unsigned long usedTime = millis() - actionStartTime;
      if(ENABLE_ACTIONS_DEBUG) {
        Serial.print("Water add - valve close! Max water level reached! ");
        Serial.print("Used time: ");
        Serial.print(usedTime);
        Serial.println(" ms");
      }
      relayHandler->closeValve();
      isWaterAdded = true;
    }

    if(millis() - actionStartTime > actionMaxTime) {
      error = true;
      if(ENABLE_ACTIONS_DEBUG) {
        Serial.println("Water add - valve close! Error: Time limit reached!");
      }
      relayHandler->closeValve();
    }
  }
}

ActionState AddWaterAction::status() {
  if(error) {
    return ActionState::ERROR;
  } else if(isWaterAdded) {
    return ActionState::FINISHED;
  } else if(actionStarted) {
    return ActionState::IN_PROGRESS;
  } else {
    return ActionState::NOT_STARTED;
  }
}

int AddWaterAction::timeLeft() {
  return 0; //ERROR_WATER_ADD_TIME_LIMIT_REACHED;
}

AddWaterAction::AddWaterAction(SafetyHandler* safetyHandler, RelayHandler* relayHandler, SensorHandler* sensorHandler) {
  error = false;
  actionMaxTime = MAX_ALLOWED_TIME_ADD_WATER * 1000;
  isWaterAdded = false;
  actionStarted = false;
  this->sensorHandler = sensorHandler;
  this->relayHandler = relayHandler;
  this->safetyHandler = safetyHandler;
}

int AddWaterAction::averageTime() {
  return 10000;
}

int AddWaterAction::getErrorCode() {
  return ERROR_WATER_ADD_TIME_LIMIT_REACHED;
}