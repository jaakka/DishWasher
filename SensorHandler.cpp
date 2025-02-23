#include "OnOffSensor.h"
#include "TemperatureSensor.h"
#include "QualitySensor.h"
#include "SensorHandler.h"
#include "Wiring.h"
#include "Config.h"

void SensorHandler::begin() {
    sensors[0] = new OnOffSensor(DOOR_SENSOR_PIN);
    sensors[1] = new OnOffSensor(FLOOD_SENSOR_PIN);
    sensors[2] = new OnOffSensor(OVERHEAT_SENSOR_PIN);
    sensors[3] = new OnOffSensor(LEVEL_SENSOR_PIN);
    sensors[4] = new OnOffSensor(QUANTITY_SENSOR_PIN);
    sensors[5] = new TemperatureSensor();
    sensors[6] = new QualitySensor();

    // NOTE - if add sensors to the array, remember to update TOTAL_SENSORS
}  
    
void SensorHandler::loop() {
    if (millis() - lastReadTime > SENSORS_READ_INTERVAL_MS) {
        lastReadTime = millis();
        for (int i = 0; i < TOTAL_SENSORS; i++) {
            sensors[i]->loop();
        }
    }
    
    if (ENABLE_SENSORS_DEBUG && millis() - lastDebugMsgTime > SENSORS_DEBUG_INTERVAL_MS) {
        lastDebugMsgTime = millis();
        printDebugMsg();
    }
}

void SensorHandler::printDebugMsg() {
    Serial.print("Door: ");
    Serial.print(doorIsOpen() ? "Open" : "Closed");
    Serial.print(", Flood: ");
    Serial.print(floodDetected() ? "Detected" : "Not Detected");
    Serial.print(", Overheat: ");
    Serial.print(overheating() ? "Detected" : "Not Detected");
    Serial.print(", Water Level: ");
    Serial.print(waterLevelMax() ? "Max" : "Not Max");
    Serial.print(", Water Quality: ");
    Serial.print(waterAnalogQualityGood() ? "Good" : "Bad");
    Serial.print(", Temperature: ");
    Serial.print(getTemperature());
    Serial.print(temperatureAreRealistic() ? " Realistic" : " Unrealistic");
    Serial.print(", Quality: ");
    Serial.println(getQuality());
}

bool SensorHandler::doorIsOpen() { // Flipped logic for more safety
    return !sensors[0]->getSensorState();
}

bool SensorHandler::doorIsClosed() {
    return sensors[0]->getSensorState();
}

bool SensorHandler::floodDetected() { // Flipped logic for more safety
    return !sensors[1]->getSensorState();
}

bool SensorHandler::noFloodDetected() {
    return sensors[1]->getSensorState();
}

bool SensorHandler::overheating() {
    return sensors[2]->getSensorState();
}

bool SensorHandler::notOverheating() {
    return !sensors[2]->getSensorState();
}

bool SensorHandler::waterLevelNotMax() {
    return sensors[3]->getSensorState();
}

bool SensorHandler::waterLevelMax() {
    return !sensors[3]->getSensorState();
}

bool SensorHandler::waterAnalogQualityGood() {
    return sensors[4]->getSensorState();
}

bool SensorHandler::waterAnalogQualityBad() {
    return !sensors[4]->getSensorState();
}

float SensorHandler::getTemperature() {
    return 10;//sensors[5]->getSensorValue();
}

bool SensorHandler::temperatureAreRealistic() {
    return true; //sensors[5]->getSensorValue() > MIN_REALISTIC_TEMPERATURE && sensors[5]->getSensorValue() < MAX_REALISTIC_TEMPERATURE;
}

float SensorHandler::getQuality() {
    return sensors[6]->getSensorValue();
}