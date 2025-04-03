#include "CheckWaterQualityAction.h"

CheckWaterQualityAction::CheckWaterQualityAction(SensorHandler* sensorHandler, int &positionRef, const int targetQuality, int failJumpPos, int successJumpPos) {
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
        startTime = millis();
        testTime = millis() - WATER_QUALITY_TEST_MS;
        actionStarted = true;
        // Get start values to list
        for(int i=0; i<totalMeasures; i++) {
            measurements[i] = this->getCalibratedQuality();
        }
    }
    else
    {
        if(millis() - startTime < (unsigned long)WATER_QUALITY_CHECK_TIME * 1000) {
            if(millis() - testTime > WATER_QUALITY_TEST_MS) {
                addMeasure(getCalibratedQuality());
                testTime = millis();
            }
        } else {
            if(this->getAverageMeasure() >= targetQuality)
            {
                *positionRef = successJumpPos;
                // Water quality pass
            }
            else
            {
                actionStarted = false;
                // Jump program start/target pos
                *positionRef = failJumpPos;
            }
            actionFinished = true;
            Serial.println("aika loppu");
        }
    }
}

void CheckWaterQualityAction::addMeasure(float value) {
    for(int i = 0; i < totalMeasures - 1; i++) {
        measurements[i] = measurements[i + 1];
    }
    measurements[totalMeasures - 1] = value;
}

float CheckWaterQualityAction::getAverageMeasure() {
    float total = 0;
    for(int i = 0; i<totalMeasures; i++) {
        total+= measurements[i];
    }
    return total/totalMeasures;
}

float CheckWaterQualityAction::getCalibratedQuality() {
    int cleanWaterCalib = MachineLearning::getValue(MachineData::QualityCalibration);
    return ( ( (float)sensorHandler->getQuality()/cleanWaterCalib) * 100 );
}


String CheckWaterQualityAction::getInfo() {
    return String((int)this->getAverageMeasure()) + "/" + String(targetQuality);
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