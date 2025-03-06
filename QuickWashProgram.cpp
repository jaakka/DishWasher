#include "QuickWashProgram.h"

QuickWashProgram::QuickWashProgram(SafetyHandler* safetyHandler, RelayHandler* relayHandler, SensorHandler* sensorHandler) {
    this->safetyHandler = safetyHandler;
    this->relayHandler = relayHandler;
    this->sensorHandler = sensorHandler;
    
    actions[0] = new AddWaterAction(safetyHandler, relayHandler, sensorHandler);
    actions[1] = new HeatWaterAction(safetyHandler, relayHandler, sensorHandler, 65);
    actions[2] = new AddSoapAction(safetyHandler, relayHandler); // soap time is now longer because hand soap is used (1min)
    actions[3] = new WashAction(safetyHandler, relayHandler, sensorHandler, 60 * 20);
    actions[4] = new EmptyWaterAction(safetyHandler, relayHandler, sensorHandler);
    actions[5] = new AddWaterAction(safetyHandler, relayHandler, sensorHandler);
    actions[6] = new WashAction(safetyHandler, relayHandler, sensorHandler, 60 * 10);
    actions[7] = new EmptyWaterAction(safetyHandler, relayHandler, sensorHandler);

    // NOTE - Remember update TOTAL_ACTIONS if you add more actions
    error = false;
}
  
void QuickWashProgram::loop() {
   if(currentAction < TOTAL_ACTIONS && !error) {
        ActionState state = actions[currentAction]->status();
        
        if(state == ActionState::ERROR) {
          errorCode = actions[currentAction]->getErrorCode();
          error = true;
        } else {
          if(state != ActionState::FINISHED) {
            actions[currentAction]->execute();
          } else {
            currentAction++;
          }
        }
    }
}

String QuickWashProgram::getCurrentActionInfo() {
  return actions[currentAction]->getInfo();
}
      
int QuickWashProgram::getDuration() {
    int duration = 0;
    for(int i = 0; i < TOTAL_ACTIONS; i++) {
        duration += actions[i]->getDuration();
    }
    return duration;
}

int QuickWashProgram::getRemainingDuration() {
  int duration = actions[currentAction]->getRemainingDuration();
  for (int i = currentAction + 1; i < TOTAL_ACTIONS; i++) {
      duration += actions[i]->getDuration();
  }
  return duration;
}

int QuickWashProgram::getErrorCode() {
  if(error) {
    return errorCode;
  } else {
    return NO_ERROR;
  }
}

ActionName QuickWashProgram::getCurrentAction() { 
  return actions[currentAction]->getName(); 
}

int QuickWashProgram::getCurrentActionDuration() { 
  return actions[currentAction]->getRemainingDuration(); 
}
