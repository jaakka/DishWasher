#include "DishWasher.h"


DishWasher dishWasher;

void setup() {
    Serial.begin(115200);
    MachineLearning::printLearnedData();
    dishWasher.begin();
}

void loop() {
    dishWasher.loop();
}

/*

TODO LIST:
- Remove DishWasher.h and DishWasher.cpp and move all the code to DishWasher.ino
- convert some ints to unsigned long (int is 32767)

wlan notes
AT+CWJAP="wlan","password"
AT+CWHOSTNAME="DishWasher6000"
*/