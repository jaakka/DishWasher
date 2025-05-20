#ifndef MACHINELEARNING_H
#define MACHINELEARNING_H

#include <EEPROM.h>
#include <Arduino.h>

enum class MachineData
{
    HeatingTime = 0, // heating time is 2 x 8 bit, because it longer than 5 min. 255 = 4.25m , 8 bit is value and next 8 is multiplier for 255s 
    FillTime = 2,
    QualityCalibrationTime = 3,
    QualityCheckTime = 4,
    QualityCalibration = 5
};

enum class BitCount
{
    bit_8 = 0,
    bit_16 = 1
};

class MachineLearning
{
    public:
        static void learnData(MachineData data, int timeInSeconds);
        static int learnedData(MachineData data);
        static int getValue(MachineData data, BitCount bits = BitCount::bit_8);
        static void setValue(MachineData data, int value = 0, BitCount bits = BitCount::bit_8);
        static void printLearnedData();
    private:
        static int calcAverage(MachineData data, int value);
};

#endif