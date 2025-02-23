#ifndef RELAYHANDLER_H
#define RELAYHANDLER_H

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
};

#endif