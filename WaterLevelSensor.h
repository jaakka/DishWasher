#ifndef WATERLEVELSENSOR_H
#define WATERLEVELSENSOR_H

#include "Sensor.h"

class WaterLevelSensor : public Sensor {
    public:
      WaterLevelSensor();
      void loop() override;
    private:
      bool maxLevel;
};

#endif