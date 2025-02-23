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
      virtual int timeLeft() = 0;
      virtual int averageTime() = 0; 
      virtual int getErrorCode() = 0;
};

#endif