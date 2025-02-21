#include "DishWasher.h"
#include "UserControl.h"
#include "RelayHandler.h"
#include <Arduino.h>
#include "Config.h"

void DishWasher::begin() {
  relayHandler.begin();
  userControl.begin();
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
    //Serial.println("ok");
    lcdHandler.UpdateText(0,"OK");
    if(!buttonPressed) {
      lcdHandler.UpdateText(0,"Sammutetaan");
      delay(1000);
      relayHandler.mainPowerOff();
    }
  }
  else 
  {
    buttonPressed = false;
  }

  if(userControl.userScrollLeft()) {
    Serial.println("vasen");
    lcdHandler.UpdateText(0,"VASEN");
  }
  if(userControl.userScrollRight()) {
    Serial.println("right");
    lcdHandler.UpdateText(0,"OIKEA");
  }

}