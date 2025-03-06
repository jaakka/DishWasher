#ifndef PROGRAM_H
#define PROGRAM_H

#include "Action.h"

class Program {
    public:
      virtual void loop() = 0;
      virtual int getDuration() = 0;
      virtual int getRemainingDuration() = 0;
      virtual ActionName getCurrentAction() = 0;
      virtual int getCurrentActionDuration() = 0;
};

#endif