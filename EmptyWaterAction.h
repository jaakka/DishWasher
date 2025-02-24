#ifndef EMPTYWATERACTION_H
#define EMPTYWATERACTION_H
#include "RelayHandler.h"
#include "SafetyHandler.h"
#include "SensorHandler.h"
#include "Action.h"
#include "ErrorCodes.h"
#include "Config.h"
#include <Arduino.h>

class EmptyWaterAction : public Action {
  public:
    EmptyWaterAction(SafetyHandler* safetyHandler, RelayHandler* relayHandler, SensorHandler* sensorHandler);
    void execute() override;
    ActionState status() override;
    int timeLeftInSeconds() override;
    int averageTimeInSeconds() override;
    int getErrorCode() override;
  private:
    RelayHandler* relayHandler;
    SafetyHandler* safetyHandler;
    SensorHandler* sensorHandler;
    unsigned long startTime;
    bool actionStarted;
    bool waterIsMaxOnStart;
    int errorCode;
    bool error;
    bool actionFinished;
};

#endif