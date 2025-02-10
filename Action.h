#ifndef ACTION_H
#define ACTION_H

class Action {
    public:
      virtual void execute() = 0;
      virtual bool isReady() = 0;
};

#endif