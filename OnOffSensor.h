#ifndef ONOFFSENSOR_H
#define ONOFFSENSOR_H

#include "Sensor.h"
#include "Config.h"
#include <Arduino.h>

class OnOffSensor : public Sensor {
    public:
        OnOffSensor(int sensorPin);
        void loop() override;
        bool getSensorState() override;
        float getSensorValue() override { return 0; };
    private:
        int sensorValue;
        int sensorPin;
};

#endif