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
    ActionName getName() override { return ActionName::EMPTY_WATER; }
    int getRemainingDuration() override;
    int getDuration() override;
    int getErrorCode() override;
    void reload() override {actionStarted = false; actionFinished = false;}
    String getInfo() override { return "EMPTY"; } // this is for debug
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