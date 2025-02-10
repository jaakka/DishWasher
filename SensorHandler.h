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
};

#endif