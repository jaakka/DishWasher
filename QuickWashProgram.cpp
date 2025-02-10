#include "QuickWashProgram.h"
#include "AddWaterAction.h"
#include "HeatWaterAction.h"
#include "AddSoapAction.h"

QuickWashProgram::QuickWashProgram() {
    actions[0] = new AddWaterAction();
    actions[1] = new HeatWaterAction();
    actions[2] = new AddSoapAction();
}
  
void QuickWashProgram::loop() {
  
}
      
int QuickWashProgram::getDurationMs() {
    return 0;
}