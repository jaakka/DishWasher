#ifndef ADDSOAPACTION_H
#define ADDSOAPACTION_H

#include "Action.h"

class AddSoapAction : public Action {
    public:
      void execute() override;
      bool isReady() override;
};

#endif