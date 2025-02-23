#ifndef ADDSOAPACTION_H
#define ADDSOAPACTION_H

#include "RelayHandler.h"
#include "SensorHandler.h"

#include "Action.h"

class AddSoapAction : public Action {
    public:
      AddSoapAction(RelayHandler* relayHandler);
      void execute() override;
      ActionState status() override;
      int timeLeft() override;
      int averageTime() override;
      int getErrorCode() override;
    private:
      bool actionStarted;
      bool actionFinished;
      unsigned long startTime;
      RelayHandler* relayHandler;
};

#endif