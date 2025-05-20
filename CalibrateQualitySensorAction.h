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
        int getDuration() override;
        void reload() override {}
        int getErrorCode() override {return NO_ERROR;}
        String getInfo() override {return "Odota";}
    private:
        static const int totalMeasures = 10;
        int averageTime;
        float measurements[totalMeasures];
        float getMaxDiff();
        void addMeasure(float value);
        float getAverageMeasure();
        bool actionStarted;
        bool actionFinished;
        bool error;
        unsigned long startTime;
        unsigned long lastMeasure;
        unsigned long realStartTime;
        SensorHandler* sensorHandler;
};

#endif