#ifndef CALIBRATEQUALITYSENSORACTION_H
#define CALIBRATEQUALITYSENSORACTION_H

#include "ErrorCodes.h"
#include "SensorHandler.h"
#include "Config.h"
#include "Action.h"
#include <Arduino.h>

class CalibrateQualitySensorAction : public Action {
    public:
        CalibrateQualitySensorAction(SensorHandler* sensorHandler);
        void execute() override;
        ActionState status() override;
        ActionName getName() override { return ActionName::CALIBRATE_QUALITY; }
        int getRemainingDuration() override;
        int getDuration() override {return WATER_QUALITY_CALIBRATE_TIME;}
        void reload() override {}
        int getErrorCode() override {return NO_ERROR;}
        String getInfo() override {return "Odota";}
    private:
        static const int totalMeasures = 10;
        float measurements[totalMeasures];
        void addMeasure(float value);
        float getAverageMeasure();
        bool actionStarted;
        bool actionFinished;
        bool error;
        unsigned long startTime;
        unsigned long lastMeasure;
        SensorHandler* sensorHandler;
};

#endif