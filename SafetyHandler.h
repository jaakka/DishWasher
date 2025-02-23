#ifndef SAFETYHANDLER_H
#define SAFETYHANDLER_H

#include "SensorHandler.h"

enum SafetyState
{
    OK,
    PAUSE,
    ERROR
};

class SafetyHandler
{
  public:
    SafetyHandler(SensorHandler* sensorHandler);
    void begin();
    void loop();
    SafetyState getState();
  
  private:
    SafetyState state;
    SensorHandler* sensorHandler;
    bool checkOverheat();
    bool checkFlood();
    bool checkDoor();
};

#endif