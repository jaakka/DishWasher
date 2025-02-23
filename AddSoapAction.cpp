#include "AddSoapAction.h"
#include "RelayHandler.h"
#include <Arduino.h>
#include "Config.h"

AddSoapAction::AddSoapAction(RelayHandler* relayHandler) {
    this->relayHandler = relayHandler;  
    actionStarted = false;
    actionFinished = false;
}

void AddSoapAction::execute() {
    if(!actionStarted) {
        relayHandler->openSoapDoor();
        if(ENABLE_ACTIONS_DEBUG) {
            Serial.println("Soap door opened");
        }
        actionStarted = true;
        startTime = millis();
    } else {
        if(millis() - startTime > (ACTION_SOAPDOOR_WAIT * 1000)) {
            relayHandler->closeSoapDoor();
            actionFinished = true;
            if(ENABLE_ACTIONS_DEBUG) {
                Serial.println("Soap door closed");
            }
        }
    }
}

ActionState AddSoapAction::status() {
    if(actionStarted) {
        if(actionFinished) {
            return ActionState::FINISHED;
        } else {
            return ActionState::IN_PROGRESS;
        }
    } else {
        return ActionState::NOT_STARTED;
    }
}

int AddSoapAction::timeLeft() {
    return (ACTION_SOAPDOOR_WAIT * 1000) - (millis() - startTime);
}

int AddSoapAction::averageTime() {
    return 10;
}

int AddSoapAction::getErrorCode() {
    return 0;
}