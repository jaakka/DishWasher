#include "QuickWashProgram.h"

QuickWashProgram::QuickWashProgram(SafetyHandler* safetyHandler, RelayHandler* relayHandler, SensorHandler* sensorHandler) {
    this->safetyHandler = safetyHandler;
    this->relayHandler = relayHandler;
    this->sensorHandler = sensorHandler;

    // Optimized version for RAM
    error = false;
    actionAvailable = false;
}
  

void QuickWashProgram::loop() {

  if(currentAction % 2 == 1) {
    if(currentActionObj != nullptr) {
      actionAvailable = false;
      delete currentActionObj;
      currentActionObj = nullptr;
    }
  }

  // Water quality check
  if (currentAction == 1) {
    currentActionObj = new AddWaterAction(safetyHandler, relayHandler, sensorHandler);
  } else if (currentAction == 3) {
    currentActionObj = new WashAction(safetyHandler, relayHandler, sensorHandler, 60 * 10);
  } else if (currentAction == 5) {
    currentActionObj = new CheckWaterQualityAction(sensorHandler, currentAction, 90, 7, 15, 1); // jump 9 if fail, if success jump 15, not need more than 1 try times because it forward command always
  } else 
  
  // Dirty wash
  if (currentAction == 7) {
    currentActionObj = new EmptyWaterAction(safetyHandler, relayHandler, sensorHandler);
  } else if (currentAction == 9) {
    currentActionObj = new AddWaterAction(safetyHandler, relayHandler, sensorHandler);
  } else if (currentAction == 11) {
    currentActionObj = new WashAction(safetyHandler, relayHandler, sensorHandler, 60 * 10);
  } else if (currentAction == 13) {
    currentActionObj = new CheckWaterQualityAction(sensorHandler, currentAction, 90, 7, 15, 2);
  } else 
  
  // Basic wash
  if (currentAction == 15) {
    currentActionObj = new EmptyWaterAction(safetyHandler, relayHandler, sensorHandler);
  } else if (currentAction == 17) {
    currentActionObj = new AddWaterAction(safetyHandler, relayHandler, sensorHandler);
  } else if (currentAction == 19) {
    currentActionObj = new AddSoapAction(safetyHandler, relayHandler);
  } else if (currentAction == 21) {
    currentActionObj = new HeatWaterAction(safetyHandler, relayHandler, sensorHandler, 65);
  } else if (currentAction == 23) {
    currentActionObj = new WashAction(safetyHandler, relayHandler, sensorHandler, 60 * 20);
  } else if (currentAction == 25) {
    currentActionObj = new EmptyWaterAction(safetyHandler, relayHandler, sensorHandler);
  } else if (currentAction == 27) {
    currentActionObj = new AddWaterAction(safetyHandler, relayHandler, sensorHandler);
  } else if (currentAction == 29) {
    currentActionObj = new WashAction(safetyHandler, relayHandler, sensorHandler, 60 * 10);
  } else if (currentAction == 31) {
    currentActionObj = new EmptyWaterAction(safetyHandler, relayHandler, sensorHandler);
  }

  if(currentAction % 2 == 1) {
    currentAction++;
  }

  //Handle actions
  if(currentAction % 2 == 0) {
    ActionState status = currentActionObj->status();
    if(status != ActionState::ERROR) {

      if(status == ActionState::IN_PROGRESS || status == ActionState::NOT_STARTED) {
        currentActionObj->execute();
        actionAvailable = true;
      }

      if(status == ActionState::FINISHED) {
        bool autonext = currentActionObj->getName() != ActionName::CHECK_QUALITY;
        actionAvailable = false;
        delete currentActionObj;
        if(autonext) {
          currentAction++;
        }
      }

    }

    if(status == ActionState::ERROR) {
      errorCode = currentActionObj->getErrorCode();
      error = true;
    }
  }
}

String QuickWashProgram::getCurrentActionInfo() {
  if (actionAvailable) {
    return currentActionObj->getInfo();
  }
  return "Valmis";
}
      
int QuickWashProgram::getDuration() { 
    return 10;
}

int QuickWashProgram::getRemainingDuration() {
  return 10;
}

int QuickWashProgram::getErrorCode() {
  if(error) {
    return errorCode;
  } 
  return NO_ERROR;
}

ActionName QuickWashProgram::getCurrentAction() { 
  if (actionAvailable) {
    return currentActionObj->getName();
  }
  return ActionName::NO_ACTION;
}

int QuickWashProgram::getCurrentActionDuration() { 
  if (actionAvailable) {
    return currentActionObj->getRemainingDuration();
  }
  return 0;
}
