#ifndef SENSOR_H
#define SENSOR_H

class Sensor {
    public:
      virtual void loop() = 0;
      virtual bool getSensorState() = 0;
      virtual float getSensorValue() = 0;
};

#endif