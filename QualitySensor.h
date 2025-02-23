#ifndef QUALITYSENSOR_H
#define QUALITYSENSOR_H

#include "Sensor.h"

class QualitySensor : public Sensor {
  public:
    QualitySensor();
    void begin();
    void loop();
    bool getSensorState() override { return false; };
    float getSensorValue() override;
  private:
    float sensorValue;
};

#endif