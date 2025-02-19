#include "DishWasher.h"

DishWasher dishWasher;

void setup() {
    Serial.begin(9600);
    dishWasher.begin();
}

void loop() {
    dishWasher.loop();
}