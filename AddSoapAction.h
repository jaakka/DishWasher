#include "Action.h"

class AddSoapAction : public Action {
    public:
      void execute() override;
      bool isReady() override;
};