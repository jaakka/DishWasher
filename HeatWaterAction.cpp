#include "HeatWaterAction.h"
#include "ErrorCodes.h"
#include "Config.h"
#include <Arduino.h>

void HeatWaterAction::execute() {
    if(!actionStarted && sensorHandler->temperatureAreRealistic()) {
        relayHandler->heatWater();
        actionStarted = true;
        if(ENABLE_ACTIONS_DEBUG) {
            Serial.println("Heating water started");
        }
    }
    if(actionStarted && sensorHandler->getTemperature() >= temp) {
        relayHandler->stopHeatingWater();
        actionFinished = true;
        if(ENABLE_ACTIONS_DEBUG) {
            Serial.println("Heating water finished");
        }
    }
    if(!sensorHandler->temperatureAreRealistic()) {
        error = true;
        relayHandler->stopHeatingWater();
        if(ENABLE_ACTIONS_DEBUG) {
            Serial.println("Heating water error - temperature not realistic");
        }
    }
}

ActionState HeatWaterAction::status() {
    if(error) {
        return ActionState::ERROR;
    }
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

int HeatWaterAction::timeLeft() {
    return 0;
}

HeatWaterAction::HeatWaterAction(SensorHandler* sensorHandler, RelayHandler* relayHandler, int temp) {
    this->relayHandler = relayHandler;
    this->sensorHandler = sensorHandler;
    this->temp = temp;
    this->actionStarted = false;
    error = false;
    actionFinished = false;
}

int HeatWaterAction::averageTime() {
    return 0;
}

int HeatWaterAction::getErrorCode() {
    return ERROR_WATER_HEAT_TIME_LIMIT_REACHED;
}

