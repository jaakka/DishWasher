#ifndef HEAT_WATER_ACTION_H
#define HEAT_WATER_ACTION_H

#include "Action.h"

class HeatWaterAction : public Action {
  public:
    void execute() override;
    bool isReady() override;
};

#endif