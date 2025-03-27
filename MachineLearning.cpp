#include "HardwareSerial.h"
#include "MachineLearning.h"

void MachineLearning::learnData(MachineData data, int value) {
    int newValue = value; //calcAverage(data, value); use average later

    /*Serial.println("============ Machine learned ============");
    if(data == MachineData::FillTime) {
      Serial.print("Fill time: ");
    } else {
      Serial.print("Heat time: ");
    }
    Serial.println(newValue);*/
    setValue(data, newValue);
}

int MachineLearning::learnedData(MachineData data) {
  if (data == MachineData::HeatingTime) {
    return getValue(data,BitCount::bit_16);
  }
  return getValue(data);
}

void MachineLearning::printLearnedData() {
    /*Serial.println("============ Machine learn data ============");
    Serial.println("Fill time: "+String(getValue(MachineData::FillTime))+"s");
    Serial.println("Heat time: "+String(getValue(MachineData::HeatingTime))+"s");*/
}

int MachineLearning::getValue(MachineData data, BitCount bits)
{
  uint8_t first_8_bits = EEPROM.read(static_cast<int>(data));

  if(bits == BitCount::bit_8) {
    return first_8_bits;
  }

  if(bits == BitCount::bit_16) {
    uint8_t last_8_bits = EEPROM.read(static_cast<int>(data) + 1);
    int16_t value = (static_cast<int16_t>(last_8_bits) << 8) | first_8_bits; // Combine the two bytes into a single 16-bit integer
    return value;
  }

  return 0; // Default case, should not happen
}

void MachineLearning::setValue(MachineData data, int value, BitCount bits)
{
    int oldValue = getValue(data, bits);
    if(oldValue != value) // Save only updated values
    {
        if(bits == BitCount::bit_16) {
            EEPROM.write(static_cast<int>(data), value & 0xFF); // Store the lower 8 bits
            EEPROM.write(static_cast<int>(data) + 1, (value >> 8) & 0xFF); // Store the upper 8 bits
        } else if(bits == BitCount::bit_8) {
            EEPROM.write(static_cast<int>(data), value);
        }
    }
}

int MachineLearning::calcAverage(MachineData data, int value)
{
    return (value + getValue(data)) / 2;
}