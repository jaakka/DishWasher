#include "Action.h" 

class AddWaterAction : public Action {
    public:
      void execute() override;
      bool isReady() override;
};