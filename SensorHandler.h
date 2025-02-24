#ifndef SENSORHANDLER_H
#define SENSORHANDLER_H

#include "OnOffSensor.h"
#include "TemperatureSensor.h"
#include "QualitySensor.h"
#include "Wiring.h"
#include "Config.h"
#include "Sensor.h"

class SensorHandler
{
  public:
    static const int TOTAL_SENSORS = 7; 
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
    bool temperatureAreRealistic();
    float getQuality();

  private:
    void printDebugMsg();
    unsigned long lastDebugMsgTime = 0;
    unsigned long lastReadTime = 0;
};

#endif