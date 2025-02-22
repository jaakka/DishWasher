#include "DishWasher.h"

DishWasher dishWasher;

void setup() {
    Serial.begin(9600);
    dishWasher.begin();
}

void loop() {
    dishWasher.loop();
}

/*

TODO LIST:
- Remove DishWasher.h and DishWasher.cpp and move all the code to DishWasher.ino

*/