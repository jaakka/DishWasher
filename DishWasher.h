#ifndef DISHWASHER_H
#define DISHWASHER_H

#include "UserControl.h"
#include "RelayHandler.h"
#include "LcdHandler.h"

class DishWasher {
  public:
    DishWasher();
    void begin();
    void loop();
  private:
    UserControl userControl;
    RelayHandler relayHandler;
    LcdHandler lcdHandler;
    bool buttonPressed;
    void powerControl();
};

#endif
