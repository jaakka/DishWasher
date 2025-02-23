#ifndef HEAT_WATER_ACTION_H
#define HEAT_WATER_ACTION_H
#include "RelayHandler.h"
#include "SensorHandler.h"
#include "Action.h"

class HeatWaterAction : public Action {
  public:
    HeatWaterAction(SensorHandler* sensorHandler, RelayHandler* relayHandler, int temp);
    void execute() override;
    ActionState status() override;
    int timeLeft() override;
    int averageTime() override;
    int getErrorCode() override;
  private:
    RelayHandler* relayHandler;
    SensorHandler* sensorHandler;
    int temp;
    bool actionStarted;
    int errorCode;
    bool error;
    bool actionFinished;
};

#endif