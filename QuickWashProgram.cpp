#include "QuickWashProgram.h"

QuickWashProgram::QuickWashProgram(SafetyHandler* safetyHandler, RelayHandler* relayHandler, SensorHandler* sensorHandler) {
    this->safetyHandler = safetyHandler;
    this->relayHandler = relayHandler;
    this->sensorHandler = sensorHandler;
    
    actions[0] = new AddWaterAction(safetyHandler, relayHandler, sensorHandler);
    actions[1] = new AddSoapAction(safetyHandler, relayHandler);
    actions[2] = new WashAction(safetyHandler, relayHandler, sensorHandler, 10);
    actions[3] = new HeatWaterAction(safetyHandler, relayHandler, sensorHandler, 40);
    actions[4] = new EmptyWaterAction(safetyHandler, relayHandler, sensorHandler);
    
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
      
int QuickWashProgram::getDurationMs() {
    return 0;
}