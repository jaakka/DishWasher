#ifndef ONOFFSENSOR_H
#define ONOFFSENSOR_H

#include "Sensor.h"

class OnOffSensor : public Sensor {
    public:
        OnOffSensor(int sensorPin);
        void loop() override;
        bool sensorState;
    private:
        int sensorPin;
};

#endif