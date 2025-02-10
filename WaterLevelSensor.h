#include "Sensor.h"

class WaterLevelSensor : public Sensor {
    public:
      WaterLevelSensor();
      void loop() override;
    private:
      bool maxLevel;
};