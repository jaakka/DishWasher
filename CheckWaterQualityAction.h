#ifndef CHECKWATERQUALITYACTION_H
#define CHECKWATERQUALITYACTION_H

#include "ErrorCodes.h"
#include "SensorHandler.h"
#include "Config.h"
#include "Action.h"
#include <Arduino.h>

class CheckWaterQualityAction : public Action {
    public:
        CheckWaterQualityAction(SensorHandler* sensorHandler, int &positionRef, const int targetQuality, int failJumpPos,int successJumpPos);
        void execute() override;
        ActionState status() override;
        ActionName getName() override { return ActionName::CHECK_QUALITY; }
        int getRemainingDuration() override;
        int getDuration() override;
        void reload() override {}
        int getErrorCode() override;
        String getInfo() override;
    private:
        static const int totalMeasures = 10;
        float measurements[totalMeasures];
        void addMeasure(float value);
        float getMaxDiff();
        float getAverageMeasure();
        float getCalibratedQuality();
        bool actionStarted;
        bool actionFinished;
        bool error;
        unsigned long startTime;
        unsigned long testTime;
        SensorHandler* sensorHandler;
        int* positionRef;
        int targetQuality;
        int failJumpPos;
        int successJumpPos;
        int tryCount;
        int maxTryTimes;
};

#endif