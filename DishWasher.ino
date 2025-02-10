#include "UserControl.h"
#include "SensorHandler.h"
#include "Action.h"

UserControl userControl;
SensorHandler sensorHandler;



void Setup() {
    userControl.Begin();
    sensorHandler.Begin();
}

void Loop() {
    sensorHandler.Loop();
}