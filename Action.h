#ifndef ACTION_H
#define ACTION_H

enum class ActionState {
  NOT_STARTED,
  IN_PROGRESS,
  FINISHED,
  ERROR
};

class Action {
    public:
      virtual void execute() = 0;
      virtual ActionState status() = 0;
      virtual int timeLeftInSeconds() = 0;
      virtual int averageTimeInSeconds() = 0; 
      virtual int getErrorCode() = 0;
};

#endif