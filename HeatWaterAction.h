#include "Action.h"

class HeatWaterAction : public Action {
  public:
    void execute() override;
    bool isReady() override;
};