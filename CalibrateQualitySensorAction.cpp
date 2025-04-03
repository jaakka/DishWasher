#include "CalibrateQualitySensorAction.h"

CalibrateQualitySensorAction::CalibrateQualitySensorAction(SensorHandler* sensorHandler) {
    this->sensorHandler = sensorHandler;
    this->actionStarted = false;
    this->actionFinished = false;
    this->error = false;
}

void CalibrateQualitySensorAction::execute() {
    if(!actionStarted) {
        lastMeasure = millis() - WATER_QUALITY_CALIBRATE_DELAY_MS;
        actionStarted = true;
        startTime = millis();
        // Get start values to list
        for(int i=0; i<totalMeasures; i++) {
            measurements[i] = sensorHandler->getQuality();
        }
    } else {
        if((millis() - startTime) < (WATER_QUALITY_CALIBRATE_TIME * 1000))
        {
            if((millis() - lastMeasure) > WATER_QUALITY_CALIBRATE_DELAY_MS)
            {
                this->addMeasure(sensorHandler->getQuality());
                lastMeasure = millis();
                Serial.println("Calibrating... "+String(getAverageMeasure()));
            }
        } else {
          if(ENABLE_MACHINE_LEARNING) {
            MachineLearning::learnData(MachineData::QualityCalibration, getAverageMeasure());
            Serial.println("Calibrated "+String(getAverageMeasure()));
          }
          actionFinished = true;
        }
    }
}

void CalibrateQualitySensorAction::addMeasure(float value) {
    for(int i = 0; i < totalMeasures - 1; i++) {
        measurements[i] = measurements[i + 1];
    }
    measurements[totalMeasures - 1] = value;
}

float CalibrateQualitySensorAction::getAverageMeasure() {
    float total = 0;
    for(int i = 0; i<totalMeasures; i++) {
        total+= measurements[i];
    }
    return total/totalMeasures;
}

ActionState CalibrateQualitySensorAction::status() {
    if(actionStarted) {
        if(actionFinished) {
            return ActionState::FINISHED;
        }
        return ActionState::IN_PROGRESS;
    } 
    return ActionState::NOT_STARTED;
}

int CalibrateQualitySensorAction::getRemainingDuration() { 
    if(actionStarted) {
        return ((WATER_QUALITY_CALIBRATE_TIME * 1000) - (millis() - startTime)) / 1000;
    } 
    return WATER_QUALITY_CALIBRATE_TIME;
}