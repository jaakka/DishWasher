#ifndef QUICKWASHPROGRAM_H
#define QUICKWASHPROGRAM_H

#include "RelayHandler.h"
#include "SensorHandler.h"
#include "Program.h"
#include "Action.h"

class QuickWashProgram : public Program {
  public:
    static const int TOTAL_ACTIONS = 3; 
    int currentAction = 0;
    Action* actions[TOTAL_ACTIONS];
    QuickWashProgram(RelayHandler* relayHandler, SensorHandler* sensorHandler);
    void loop() override;
    int getDurationMs() override;
  private:
    RelayHandler* relayHandler;
    SensorHandler* sensorHandler; 
    bool error;
    int errorCode;
};

#endif