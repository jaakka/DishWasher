#ifndef QUALITYSENSOR_H
#define QUALITYSENSOR_H

#include "Sensor.h"

class QualitySensor : public Sensor {
  public:
    // float sensorValue; Defined in Sensor.h
    QualitySensor();
    void begin();
    void loop();
};

#endif