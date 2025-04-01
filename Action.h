#ifndef ACTION_H
#define ACTION_H

#include "ErrorCodes.h"
#include <Arduino.h>

enum class ActionState {
  NOT_STARTED,
  IN_PROGRESS,
  FINISHED,
  ERROR
};

enum class ActionName {
  NO_ACTION,
  ADD_WATER,
  HEAT_WATER,
  ADD_SOAP,
  WASH,
  EMPTY_WATER,
  CHECK_QUALITY
};

class Action {
    public:
      virtual ~Action() {};

      virtual void execute() = 0;
      virtual ActionState status() = 0;
      virtual ActionName getName() = 0;
      virtual String getInfo() = 0;
      virtual int getErrorCode() = 0;
      virtual int getRemainingDuration() = 0;
      virtual int getDuration() = 0; 
      virtual void reload() = 0;
};

#endif