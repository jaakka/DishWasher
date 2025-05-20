#include "CalibrateQualitySensorAction.h"

CalibrateQualitySensorAction::CalibrateQualitySensorAction(SensorHandler* sensorHandler) {
    this->sensorHandler = sensorHandler;
    this->actionStarted = false;
    this->actionFinished = false;
    this->error = false;

    if(ENABLE_MACHINE_LEARNING) {
        averageTime = MachineLearning::getValue(MachineData::QualityCalibrationTime);
        if(averageTime == 0) {
            averageTime = WATER_QUALITY_MAX_CALIBRATE_TIME;
        }
    } else {
        averageTime = WATER_QUALITY_MAX_CALIBRATE_TIME;
    }
}

void CalibrateQualitySensorAction::execute() {
    if(!actionStarted) {
        lastMeasure = millis() - WATER_QUALITY_CALIBRATE_DELAY_MS;
        actionStarted = true;
        startTime = millis();
        realStartTime = millis();
        // Get start values to list
        for(int i=0; i<totalMeasures; i++) {
            measurements[i] = sensorHandler->getQuality();
        }
    } else {
        if((millis() - startTime) < (unsigned long)(WATER_QUALITY_MAX_CALIBRATE_TIME * 1000)) //  || getMaxDiff() < 0.1
        {
            if((millis() - lastMeasure) > WATER_QUALITY_CALIBRATE_DELAY_MS)
            {
                this->addMeasure(sensorHandler->getQuality());
                lastMeasure = millis();
                Serial.println("Calibrating... "+String(getAverageMeasure()) + " / "+String(getMaxDiff()));
            }
        } else {
            if(getMaxDiff() != 0) {
                startTime = millis() - 1000 * (WATER_QUALITY_MAX_CALIBRATE_TIME - WATER_QUALITY_MAX_RECALIBRATE_TIME) ;
            }
            else
            {
                if(ENABLE_MACHINE_LEARNING) {
                    MachineLearning::learnData(MachineData::QualityCalibration, getAverageMeasure());
                    MachineLearning::learnData(MachineData::QualityCalibrationTime, ((millis() - realStartTime)/1000) );
                    Serial.println("Machine learned " + String(((millis() - realStartTime)/1000)));
                    Serial.println("Calibrated "+String(getAverageMeasure()));
                }
                actionFinished = true;
            }
        }
    }
}

void CalibrateQualitySensorAction::addMeasure(float value) {
    Serial.println("measure added " + String(value));
    for(int i = 0; i < totalMeasures - 1; i++) {
        measurements[i] = measurements[i + 1];
    }
    measurements[totalMeasures - 1] = value;
}

float CalibrateQualitySensorAction::getMaxDiff() {
    float min = 254, max = 0;
    for(int i = 0; i<totalMeasures; i++) {
        if(measurements[i] < min || min == 254) {
            min = measurements[i];
        } else if(measurements[i] > max || max == 0) {
            max = measurements[i];
        }
    }
    return abs(max) - abs(min);
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
        return ((averageTime * 1000) - (millis() - startTime)) / 1000;
    } 
    return averageTime;
}

int CalibrateQualitySensorAction::getDuration() {
    return averageTime;
}