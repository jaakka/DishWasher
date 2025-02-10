#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include "Sensor.h"

class TemperatureSensor : public Sensor {
  public:
    TemperatureSensor();
    void loop() override;
};

#endif