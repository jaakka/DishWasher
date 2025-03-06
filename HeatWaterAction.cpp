#include "HeatWaterAction.h"

void HeatWaterAction::execute() {
    if(!actionStarted && sensorHandler->temperatureAreRealistic()) {
        if(sensorHandler->waterLevelMax()){
            relayHandler->heatWater();
            startTime = millis();
            actionStarted = true;
            if(ENABLE_ACTIONS_DEBUG) {
                Serial.println("Heating water started");
            }
        }

        if(sensorHandler->waterLevelNotMax()){
            relayHandler->stopHeatingWater();
            errorCode = ERROR_WATER_LEVEL_TOO_LOW_FOR_HEAT;
            error = true;         
            if(ENABLE_ACTIONS_DEBUG) {
                Serial.println("Heating water error - water level too low");
            }
        }
    }
    if(actionStarted && sensorHandler->getTemperature() >= temp) {
        relayHandler->stopHeatingWater();
        usedTime = (millis() - startTime) / 1000;
        actionFinished = true;
        if(ENABLE_ACTIONS_DEBUG) {
            Serial.print("Heating water finished ");
            Serial.print(usedTime);
            Serial.println(" seconds");
        }

        if(ENABLE_MACHINE_LEARNING) {
            MachineLearning::learnData(MachineData::HeatingTime, usedTime);
        }
    }
    if(!sensorHandler->temperatureAreRealistic()) {
        error = true;
        relayHandler->stopHeatingWater();
        if(ENABLE_ACTIONS_DEBUG) {
            Serial.println("Heating water error - temperature not realistic");
        }
    }
    if(millis() - startTime > (unsigned long)MAX_ALLOWED_TIME_HEAT_WATER * 1000) {
        errorCode = ERROR_WATER_HEAT_TIME_LIMIT_REACHED;
        error = true;
        relayHandler->stopHeatingWater();

        if(ENABLE_ACTIONS_DEBUG) {
            Serial.println("Heating water error - time limit reached");
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

int HeatWaterAction::getRemainingDuration() {
    return averageTime - (millis() - startTime) / 1000;
}

HeatWaterAction::HeatWaterAction(SafetyHandler* safetyHandler, RelayHandler* relayHandler, SensorHandler* sensorHandler, int temp) {
    this->relayHandler = relayHandler;
    this->sensorHandler = sensorHandler;
    this->temp = temp - TEMP_OFFSET;
    this->actionStarted = false;
    error = false;
    usedTime = 0;
    actionFinished = false;

    if(ENABLE_MACHINE_LEARNING) {
        averageTime = MachineLearning::getValue(MachineData::HeatingTime);
        if(averageTime == 0) {
            averageTime = MAX_ALLOWED_TIME_HEAT_WATER;
        }
    } else {
        averageTime = MAX_ALLOWED_TIME_HEAT_WATER;
    }
}

int HeatWaterAction::getDuration() {
    return averageTime;
}

int HeatWaterAction::getErrorCode() {
    return errorCode;
}

