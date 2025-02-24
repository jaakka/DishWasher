#ifndef ADDSOAPACTION_H
#define ADDSOAPACTION_H

#include "RelayHandler.h"
#include "SensorHandler.h"
#include "SafetyHandler.h"
#include "RelayHandler.h"
#include "SafetyHandler.h"
#include "Config.h"
#include "Action.h"
#include <Arduino.h>

class AddSoapAction : public Action {
    public:
      AddSoapAction(SafetyHandler* safetyHandler, RelayHandler* relayHandler);
      void execute() override;
      ActionState status() override;
      int timeLeftInSeconds() override;
      int averageTimeInSeconds() override;
      int getErrorCode() override;
    private:
      bool actionStarted;
      bool actionFinished;
      unsigned long startTime;
      RelayHandler* relayHandler;
      SafetyHandler* safetyHandler;
};

#endif