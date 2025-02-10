#include "WaterLevelSensor.h"
#include "TemperatureSensor.h"
#include "SensorHandler.h"

void SensorHandler::begin() {
    sensors[0] = new WaterLevelSensor();
    sensors[1] = new TemperatureSensor();
}  
    
void SensorHandler::loop() {
    for (int i = 0; i < TOTAL_SENSORS; i++) {
        sensors[i]->loop();
    }
}
