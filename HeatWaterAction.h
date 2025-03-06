#ifndef HEATWATERACTION_H
#define HEATWATERACTION_H
#include "RelayHandler.h"
#include "SensorHandler.h"
#include "SafetyHandler.h"
#include "Action.h"
#include "ErrorCodes.h"
#include "Config.h"
#include "MachineLearning.h"
#include <Arduino.h>

class HeatWaterAction : public Action {
  public:
    HeatWaterAction(SafetyHandler* safetyHandler, RelayHandler* relayHandler, SensorHandler* sensorHandler, int temp);
    void execute() override;
    ActionState status() override;
    ActionName getName() override { return ActionName::HEAT_WATER; }
    int getRemainingDuration() override;
    int getDuration() override;
    int getErrorCode() override;
    String getInfo() override;
  private:
    RelayHandler* relayHandler;
    SensorHandler* sensorHandler;
    SafetyHandler* safetyHandler;
    int averageTime;
    unsigned long startTime;
    int usedTime;
    int temp;
    bool actionStarted;
    int errorCode;
    bool error;
    bool actionFinished;
};

#endif