#include "AddSoapAction.h"

AddSoapAction::AddSoapAction(SafetyHandler* safetyHandler, RelayHandler* relayHandler) {
    this->safetyHandler = safetyHandler;
    this->relayHandler = relayHandler;  
    actionStarted = false;
    actionFinished = false;
}

void AddSoapAction::execute() {
    /// TODO: Add safety 
    //if (safetyHandler->getState() == SafetyState::OK) {
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
    //}


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

int AddSoapAction::timeLeftInSeconds() {
    return (ACTION_SOAPDOOR_WAIT * 1000) - (millis() - startTime);
}

int AddSoapAction::averageTimeInSeconds() {
    return 10;
}

int AddSoapAction::getErrorCode() {
    return 0;
}