#include "MachineLearning.h"

void MachineLearning::learnData(MachineData data, int value)
{
    int newValue = value; //calcAverage(data, value); use average later
    setValue(data, newValue);
}

void MachineLearning::printLearnedData() 
{
    Serial.println("============ Machine learn data ============");
    Serial.println("Fill time: "+String(getValue(MachineData::FillTime))+"s");
    Serial.println("Heat time: "+String(getValue(MachineData::HeatingTime))+"s");
}

int MachineLearning::getValue(MachineData data)
{
    return EEPROM.read(static_cast<int>(data));
}

void MachineLearning::setValue(MachineData data, int value)
{
    int oldValue = getValue(data);
    if(oldValue != value) // Save only updated values
    {
        EEPROM.write(static_cast<int>(data), value);
    }
}

int MachineLearning::calcAverage(MachineData data, int value)
{
    return value + getValue(data) / 2;
}