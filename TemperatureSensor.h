#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include <OneWire.h>
#include <DallasTemperature.h>
#include "Sensor.h"

#define PIN_TemperatureSensor 12

class TemperatureSensor : public Sensor {
  public:
    
    TemperatureSensor();
    void loop() override;

  private:

    OneWire oneWire;              
    DallasTemperature dallasTemperature;
};

#endif
