#ifndef ADDWATERACTION_H
#define ADDWATERACTION_H

#include "RelayHandler.h"
#include "SensorHandler.h"

#include "Action.h" 

class AddWaterAction : public Action {
    public:
      AddWaterAction(SensorHandler* sensorHandler, RelayHandler* relayHandler);
      void execute() override;
      ActionState status() override;
      int timeLeft() override;
      int averageTime() override;
      int getErrorCode() override;
    private:
      int actionMaxTime;
      unsigned long actionStartTime;
      bool error;
      bool isWaterAdded;
      bool actionStarted;
      SensorHandler* sensorHandler;
      RelayHandler* relayHandler;
};

#endif