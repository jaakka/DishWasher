#ifndef WASHACTION_H
#define WASHACTION_H
#include "RelayHandler.h"
#include "SafetyHandler.h"
#include "SensorHandler.h"
#include "Action.h"
#include "ErrorCodes.h"
#include "Config.h"
#include <Arduino.h>

class WashAction : public Action {
  public:
    WashAction(SafetyHandler* safetyHandler, RelayHandler* relayHandler, SensorHandler* sensorHandler, int washTimeInSeconds);
    void execute() override;
    ActionState status() override;
    ActionName getName() override { return ActionName::WASH; }
    int getRemainingDuration() override;
    int getDuration() override;
    int getErrorCode() override;
    String getInfo() override { return "WASH"; } // this is for debug
  private:
    RelayHandler* relayHandler;
    SafetyHandler* safetyHandler;
    SensorHandler* sensorHandler;
    int washTimeInSeconds;
    unsigned long startTime;
    bool actionStarted;
    bool waterIsMaxOnStart;
    int errorCode;
    bool error;
    bool actionFinished;
};

#endif