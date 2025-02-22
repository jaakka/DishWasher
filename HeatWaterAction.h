#ifndef HEAT_WATER_ACTION_H
#define HEAT_WATER_ACTION_H

#include "Action.h"

class HeatWaterAction : public Action {
  public:
    HeatWaterAction(int temp);
    void execute() override;
    bool isReady() override;
    int timeLeft() override;
    
};

#endif