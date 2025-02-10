#include "WaterLevelSensor.h"
#include "TemperatureSensor.h"

class SensorHandler
{
  public:

    static const int TOTAL_SENSORS = 2; 
    Sensor* sensors[TOTAL_SENSORS];

    void Begin() {
        sensors[0] = new WaterLevelSensor();
        sensors[1] = new TemperatureSensor();
    }  
    
    void Loop() {
        for (int i = 0; i < TOTAL_SENSORS; i++) {
            sensors[i]->loop();
        }
    }
};