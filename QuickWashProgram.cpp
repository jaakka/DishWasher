#include "QuickWashProgram.h"

QuickWashProgram::QuickWashProgram(SafetyHandler* safetyHandler, RelayHandler* relayHandler, SensorHandler* sensorHandler) {
    this->safetyHandler = safetyHandler;
    this->relayHandler = relayHandler;
    this->sensorHandler = sensorHandler;

    // Optimized version for RAM
    error = false;
    actionAvailable = false;
    currentActionName = ActionName::WASH; // Don't use NO_ACTION, it stop program

    // This is more optimized for arduino nano ram :( 
    program[0] = {0, ActionName::ADD_WATER};
    program[1] = {0, ActionName::CALIBRATE_QUALITY};
    program[2] = {60*10, ActionName::WASH};
    program[3] = {0, ActionName::CHECK_QUALITY};
    program[4] = {0, ActionName::EMPTY_WATER};
    program[5] = {0, ActionName::ADD_WATER};
    program[6] = {60*10, ActionName::WASH};
    program[7] = {0, ActionName::EMPTY_WATER};
    program[8] = {0, ActionName::ADD_WATER};
    program[9] = {0, ActionName::HEAT_WATER};
    program[10] = {60*20, ActionName::WASH};
    program[11] = {0, ActionName::EMPTY_WATER};
    program[12] = {0, ActionName::ADD_WATER};
    program[13] = {60*10, ActionName::WASH};
    program[14] = {0, ActionName::EMPTY_WATER};
}
  

void QuickWashProgram::loop() {
    
    if(currentAction >= programLastAction) {
        Serial.println("Program - finished!");
        if(currentActionObj != nullptr) {
            delete currentActionObj;
            currentActionObj = nullptr;
        }
        currentActionName = ActionName::NO_ACTION;
        return;
    }

    if(currentActionObj == nullptr) {
    if(currentAction == 0) {
      currentActionObj = new AddWaterAction(safetyHandler, relayHandler, sensorHandler);
    } else if(currentAction == 1) {
      currentActionObj = new CalibrateQualitySensorAction(sensorHandler);
    } else if(currentAction == 2) {
      currentActionObj = new WashAction(safetyHandler, relayHandler, sensorHandler, 60 * 10);
    } else if(currentAction == 3) {
      currentActionObj = new CheckWaterQualityAction(sensorHandler, currentAction, 95, 4, 7);


    } else if(currentAction == 4) {
      currentActionObj = new EmptyWaterAction(safetyHandler, relayHandler, sensorHandler);
    } else if(currentAction == 5) {
      currentActionObj = new AddWaterAction(safetyHandler, relayHandler, sensorHandler);
    } else if(currentAction == 6) {
      currentActionObj = new WashAction(safetyHandler, relayHandler, sensorHandler, 60 * 10);


    } else if(currentAction == 7) {
      currentActionObj = new EmptyWaterAction(safetyHandler, relayHandler, sensorHandler);
    } else if(currentAction == 8) {
      currentActionObj = new AddWaterAction(safetyHandler, relayHandler, sensorHandler);
    } else if(currentAction == 9) {
      currentActionObj = new HeatWaterAction(safetyHandler, relayHandler, sensorHandler,45);
    } else if(currentAction == 10) {
      currentActionObj = new WashAction(safetyHandler, relayHandler, sensorHandler, 60 * 20);
    } else if(currentAction == 11) {
      currentActionObj = new EmptyWaterAction(safetyHandler, relayHandler, sensorHandler);
    } else if(currentAction == 12) {
      currentActionObj = new AddWaterAction(safetyHandler, relayHandler, sensorHandler);
    } else if(currentAction == 13) {
      currentActionObj = new WashAction(safetyHandler, relayHandler, sensorHandler, 60 * 10);
    } else if(currentAction == 14) {
      currentActionObj = new EmptyWaterAction(safetyHandler, relayHandler, sensorHandler);
    }

    if(currentActionObj != nullptr) {
      //Serial.println("Program - created action "+String(currentAction));
    }

    return;
  }
  
  // Action created
  if(currentActionObj != nullptr) {
    ActionState status = currentActionObj->status();
    if(status != ActionState::ERROR) {

        if(status == ActionState::IN_PROGRESS || status == ActionState::NOT_STARTED) {
          if(status == ActionState::NOT_STARTED) {
            //Serial.println("Program - action "+String(currentAction) + " starting.");
          }
          currentActionObj->execute();
        }

        if(status == ActionState::FINISHED) {
          Serial.println("Program - action "+String(currentAction) + " finished.");
          if(currentActionObj->getName() != ActionName::CHECK_QUALITY) {
            currentAction++;
          }
          delete currentActionObj;
          currentActionObj = nullptr;
          return;
        }
    }

    // check are instance still available (faster error handling)
    if(currentActionObj != nullptr) {
      if(status == ActionState::ERROR) {
        errorCode = currentActionObj->getErrorCode();
        error = true;
      }
    }
  }
}

String QuickWashProgram::getCurrentActionInfo() {
  if (currentActionObj != nullptr) {
    return currentActionObj->getInfo();
  }
  return "Valmis";
}
      
int QuickWashProgram::getDuration() { 
  int total_duration = 0;
  for (int i = 0; i<programLastAction; i++) {
    total_duration+=program[i].duration;
  }
  return total_duration;
}

int QuickWashProgram::getRemainingDuration() {
  int total_duration = 0;
  if(currentAction <= programLastAction){
    for (int i = currentAction; i<programLastAction; i++) {
      total_duration+=program[i].duration;
    }
    if (currentActionObj != nullptr) {
      total_duration += currentActionObj->getRemainingDuration();
    }
  }
  return total_duration;
}

int QuickWashProgram::getErrorCode() {
  if(error) {
    return errorCode;
  } 
  return NO_ERROR;
}

ActionName QuickWashProgram::getCurrentAction() { 
  // Update action if available
  if (currentActionObj != nullptr) {
    currentActionName = currentActionObj->getName();
  } 
  return currentActionName;
}

int QuickWashProgram::getCurrentActionDuration() { 
  if (currentActionObj != nullptr) {
    return currentActionObj->getRemainingDuration();
  }
  return 0;
}
