#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include "Wiring.h"
#include "Sensor.h"
#include <OneWire.h>
#include <DallasTemperature.h>

class TemperatureSensor : public Sensor {
  public:
    TemperatureSensor();
    void loop() override;
    bool getSensorState() override { return false; };
    float getSensorValue() override;

  private:
    OneWire oneWire;              
    DallasTemperature dallasTemperature;
    float sensorValue;
};

#endif
