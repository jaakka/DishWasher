#include "CheckWaterQualityAction.h"

CheckWaterQualityAction::CheckWaterQualityAction(SensorHandler* sensorHandler, int &positionRef, const int targetQuality, int failJumpPos, int successJumpPos, int maxTryTimes) {
    this->sensorHandler = sensorHandler;
    this->positionRef = &positionRef;
    this->targetQuality = targetQuality;
    this->failJumpPos = failJumpPos;
    this->successJumpPos = successJumpPos;
    this->maxTryTimes = maxTryTimes;
    this->actionStarted = false;
    this->actionFinished = false;
    this->error = false;
    this->tryCount = 0;
}

void CheckWaterQualityAction::execute() {
    if(!actionStarted) {
        if(maxTryTimes > tryCount) {
            startTime = millis();
            actionStarted = true;
            tryCount++;
            Serial.println("yritetaan "+String(tryCount));
        }
        else // no more try times
        {
            *positionRef = successJumpPos;
            actionFinished = true;
            Serial.println("ei yrityksia");
        }
    }
    else
    {
        if(millis() - startTime > (unsigned long)WATER_QUALITY_CHECK_TIME * 1000) {
            if(sensorHandler->getQuality() >= targetQuality)
            {
                *positionRef = successJumpPos;
                // Water quality pass
                actionFinished = true;
            }
            else
            {
                actionStarted = false;
                // Jump program start/target pos
                *positionRef = failJumpPos;
            }
            Serial.println("aika loppu");
        }
    }
}

String CheckWaterQualityAction::getInfo() {
    return String(sensorHandler->getQuality()) + "/" + String(targetQuality);
}

ActionState CheckWaterQualityAction::status() {
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

int CheckWaterQualityAction::getRemainingDuration() { 
    if(!actionStarted) {
        return WATER_QUALITY_CHECK_TIME;
    }
    return (WATER_QUALITY_CHECK_TIME * 1000 - (millis() - startTime)) / 1000;
}

int CheckWaterQualityAction::getDuration() {
    return WATER_QUALITY_CHECK_TIME;  
}

int CheckWaterQualityAction::getErrorCode() {
    return ERROR_WATER_QUALITY;
}