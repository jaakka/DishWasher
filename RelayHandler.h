#ifndef RELAYHANDLER_H
#define RELAYHANDLER_H

#include "Wiring.h"
#include <Arduino.h>

class RelayHandler
{
  public:
    void begin();
    void mainPowerOff();  
    void openValve();
    void closeValve();
    void openSoapDoor();
    void closeSoapDoor();
    void heatWater();
    void stopHeatingWater();
    void startEmptyPump();
    void stopEmptyPump();
    void startWashPump();
    void stopWashPump();
};

#endif