#ifndef MACHINELEARNING_H
#define MACHINELEARNING_H

#include <EEPROM.h>
#include <Arduino.h>

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
        static void printLearnedData();
    private:
        static int calcAverage(MachineData data, int value);
};

#endif