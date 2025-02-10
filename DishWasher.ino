#include "UserControl.h"
#include "SensorHandler.h"
#include "Action.h"

UserControl userControl;
SensorHandler sensorHandler;

void setup() {
    userControl.begin();
    sensorHandler.begin();
}

void loop() {
    sensorHandler.loop();
}