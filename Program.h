#ifndef PROGRAM_H
#define PROGRAM_H

#include "Action.h"
#include <Arduino.h>

class Program {
    public:
      virtual void loop() = 0;
      virtual int getDuration() = 0;
      virtual int getRemainingDuration() = 0;
      virtual ActionName getCurrentAction() = 0;
      virtual int getCurrentActionDuration() = 0;
      virtual String getCurrentActionInfo() = 0;
      virtual int getErrorCode() = 0;
};

#endif