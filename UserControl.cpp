#include "HardwareSerial.h"
#include "UserControl.h"
#include "Arduino.h"

void UserControl::begin() {
  for(int i=0; i<10; i++) {
    buttonValues[i] = 1023;
  }
}

void UserControl::loop() {
  buttonValue = analogRead(PIN_EncoderPress);
  updateButtonValues(buttonValue);
  //Serial.println(averageButtonValues());
}

bool UserControl::userScrollRight() {
  return false;
}

bool UserControl::userScrollLeft() {
  return false;
}

bool UserControl::userPress() {
  return averageButtonValues() > 1000;
}

void UserControl::updateButtonValues(int value) {
  for (int i = 0; i < 9; i++) {
    buttonValues[i] = buttonValues[i + 1];
  }
  buttonValues[9] = value;
}

int UserControl::averageButtonValues() {
  int sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += buttonValues[i];
  }
  return sum / 10;
}