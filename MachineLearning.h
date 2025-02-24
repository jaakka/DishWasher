#ifndef MACHINELEARNING_H
#define MACHINELEARNING_H

#include <EEPROM.h>

enum class MachineData
{
    HeatingTime = 0,
    FillTime = 1
};

class MachineLearning
{
    public:
        static void learnData(MachineData data, int timeInSeconds);
        static int getValue(MachineData data);
        static void setValue(MachineData data, int value);
    private:
        static int calcAverage(MachineData data, int value);
};

#endif