#ifndef ADDWATERACTION_H
#define ADDWATERACTION_H

#include "Action.h" 

class AddWaterAction : public Action {
    public:
      void execute() override;
      bool isReady() override;
      int timeLeft() override;
};

#endif