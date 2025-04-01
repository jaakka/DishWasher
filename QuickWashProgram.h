#ifndef QUICKWASHPROGRAM_H
#define QUICKWASHPROGRAM_H

#include "RelayHandler.h"
#include "SensorHandler.h"
#include "SafetyHandler.h"
#include "Program.h"
#include "Action.h"
#include "AddWaterAction.h"
#include "HeatWaterAction.h"
#include "AddSoapAction.h"
#include "EmptyWaterAction.h"
#include "CheckWaterQualityAction.h"
#include "WashAction.h"
#include <Arduino.h>
#include "Action.h"
#include "ErrorCodes.h"

class QuickWashProgram : public Program {
  public:
    int currentAction = 0;

    QuickWashProgram(SafetyHandler* safetyHandler, RelayHandler* relayHandler, SensorHandler* sensorHandler);
    void loop() override;
    int getRemainingDuration() override;
    int getDuration() override;
    int getErrorCode() override;
    String getCurrentActionInfo() override;
    ActionName getCurrentAction() override;
    int getCurrentActionDuration() override;
    
  private:
    Action* currentActionObj;
    RelayHandler* relayHandler;
    SensorHandler* sensorHandler; 
    SafetyHandler* safetyHandler;
    bool error;
    int errorCode;
    bool actionAvailable;
};

#endif