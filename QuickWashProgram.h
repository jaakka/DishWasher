#ifndef QUICKWASHPROGRAM_H
#define QUICKWASHPROGRAM_H

#include "Program.h"
#include "Action.h"

class QuickWashProgram : public Program {
  public:
    static const int TOTAL_ACTIONS = 2; 
    int currentAction = 0;
    Action* actions[TOTAL_ACTIONS];
    QuickWashProgram();
    void loop() override;
    int getDurationMs() override;
};

#endif