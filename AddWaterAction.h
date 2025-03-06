#ifndef ADDWATERACTION_H
#define ADDWATERACTION_H

#include "RelayHandler.h"
#include "SensorHandler.h"
#include "SafetyHandler.h"
#include "Config.h"
#include "ErrorCodes.h"
#include "Action.h" 
#include "MachineLearning.h"
#include <Arduino.h>

class AddWaterAction : public Action {
    public:
      AddWaterAction(SafetyHandler* safetyHandler, RelayHandler* relayHandler, SensorHandler* sensorHandler);
      void execute() override;
      ActionState status() override;
      ActionName getName() override { return ActionName::ADD_WATER; }
      int getRemainingDuration() override;
      int getDuration() override;
      int getErrorCode() override;
      String getInfo() override { return "ADDWATER"; } // this is for debug
    private:
      unsigned long actionMaxTime;
      unsigned long actionStartTime;
      int averageTime;
      bool error;
      bool isWaterAdded;
      bool actionStarted;
      SensorHandler* sensorHandler;
      RelayHandler* relayHandler;
      SafetyHandler* safetyHandler;
};

#endif