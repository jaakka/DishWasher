#ifndef ADDSOAPACTION_H
#define ADDSOAPACTION_H

#include "RelayHandler.h"
#include "SensorHandler.h"
#include "SafetyHandler.h"
#include "Config.h"
#include "Action.h"
#include <Arduino.h>

class AddSoapAction : public Action {
    public:
      AddSoapAction(SafetyHandler* safetyHandler, RelayHandler* relayHandler);
      void execute() override;
      ActionState status() override;
      ActionName getName() override { return ActionName::ADD_SOAP; }
      int getRemainingDuration() override;
      int getDuration() override;
      int getErrorCode() override;
      void reload() override {actionStarted = false; actionFinished = false;}
      String getInfo() override { return "ADDSOAP"; } // this is for debug
    private:
      bool actionStarted;
      bool actionFinished;
      unsigned long startTime;
      RelayHandler* relayHandler;
      SafetyHandler* safetyHandler;
};

#endif