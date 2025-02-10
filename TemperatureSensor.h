#include "Sensor.h"

class TemperatureSensor : public Sensor {
  public:
    TemperatureSensor();
    void loop() override;
};