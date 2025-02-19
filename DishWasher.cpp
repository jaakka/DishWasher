#include "DishWasher.h"
#include "UserControl.h"
#include "RelayHandler.h"
#include <Arduino.h>
#include "Config.h"

void DishWasher::begin() {
  userControl.begin();
  relayHandler.begin();
  lcdHandler.begin();
}

void DishWasher::loop() {
  userControl.loop();
  powerControl();
}

DishWasher::DishWasher() {
  buttonPressed = true; 
}

void DishWasher::powerControl() {
  if(userControl.userPress()) {
    if(!buttonPressed) {
      relayHandler.mainPowerOff();
    }
  }
  else
  { 
    buttonPressed = false;
  }
}