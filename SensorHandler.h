#ifndef SENSORHANDLER_H
#define SENSORHANDLER_H

#include "Sensor.h"

class SensorHandler
{
  public:
    static const int TOTAL_SENSORS = 2; 
    Sensor* sensors[TOTAL_SENSORS];
    void begin();
    void loop();
    bool doorIsOpen();
    bool doorIsClosed();
    bool floodDetected();
    bool noFloodDetected();
    bool overheating();
    bool notOverheating();
    bool waterLevelNotMax();
    bool waterLevelMax();
    bool waterAnalogQualityGood();
    bool waterAnalogQualityBad();
    float getTemperature();
    float getQuality();

  private:
    void printDebugMsg();
};

#endif