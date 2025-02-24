#ifndef DISHWASHER_H
#define DISHWASHER_H

#include "UserControl.h"
#include "RelayHandler.h"
#include "LcdHandler.h"
#include "SensorHandler.h"
#include "SafetyHandler.h"
#include "QuickWashProgram.h"
#include "UserControl.h"
#include "RelayHandler.h"
#include "SafetyHandler.h"
#include "Config.h"
#include "LcdHandler.h"
#include "LcdValues.h"
#include <Arduino.h>

#define MENU_NOSELECTED 0
#define MENU_QUICKWASH 1
#define MENU_COLDWASH 2
#define MENU_POWERWASH 3
#define MENU_ECOWASH 4
#define MENU_HANDWASH 5
#define MENU_SETTINGS 6
#define MENU_POWEROFF 7

#define PAGE_MAIN 0
#define PAGE_QUICKWASH 1
#define PAGE_COLDWASH 2
#define PAGE_POWERWASH 3
#define PAGE_ECOWASH 4
#define PAGE_HANDWASH 5
#define PAGE_SETTINGS 6
#define PAGE_POWEROFF 7


class DishWasher {
  public:
    DishWasher();
    void begin();
    void loop();
  private:
    void changePage(int newPage);
    void updateCurrentPage();
    void updateMenu(); 
    void updateSettings();
    int selection;
    int pageId;
    int minSelection, maxSelection;
    QuickWashProgram quickWashProgram;
    SafetyHandler safetyHandler;
    UserControl userControl;
    RelayHandler relayHandler;
    LcdHandler lcdHandler;
    SensorHandler sensorHandler;
    bool buttonPressed;
    void userActions();
};

#endif
