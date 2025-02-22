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
}  
    
void SensorHandler::loop() {
    for (int i = 0; i < TOTAL_SENSORS; i++) {
        sensors[i]->loop();
    }

    if (ENABLE_SENSORS_DEBUG) {
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
    Serial.print(", Quality: ");
    Serial.println(getQuality());
}

bool SensorHandler::doorIsOpen() {
    return sensors[0]->sensorState;
}

bool SensorHandler::doorIsClosed() {
    return !sensors[0]->sensorState;
}

bool SensorHandler::floodDetected() {
    return sensors[1]->sensorState;
}

bool SensorHandler::noFloodDetected() {
    return !sensors[1]->sensorState;
}

bool SensorHandler::overheating() {
    return sensors[2]->sensorState;
}

bool SensorHandler::notOverheating() {
    return !sensors[2]->sensorState;
}

bool SensorHandler::waterLevelNotMax() {
    return sensors[3]->sensorState;
}

bool SensorHandler::waterLevelMax() {
    return !sensors[3]->sensorState;
}

bool SensorHandler::waterAnalogQualityGood() {
    return sensors[4]->sensorState;
}

bool SensorHandler::waterAnalogQualityBad() {
    return !sensors[4]->sensorState;
}

float SensorHandler::getTemperature() {
    return sensors[5]->sensorValue;
}

float SensorHandler::getQuality() {
    return sensors[6]->sensorValue;
}