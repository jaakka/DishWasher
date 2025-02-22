#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include <OneWire.h>
#include <DallasTemperature.h>
#include "Sensor.h"

class TemperatureSensor : public Sensor {
  public:
    TemperatureSensor();
    void loop() override;
    // float sensorValue; Defined in Sensor.h

  private:
    OneWire oneWire;              
    DallasTemperature dallasTemperature;
};

#endif
