#include "DishWasher.h"
#include "UserControl.h"
#include "RelayHandler.h"
#include <Arduino.h>
#include "Config.h"
#include "LcdHandler.h"
#include "LcdValues.h"

void DishWasher::begin() {
  relayHandler.begin();
  userControl.begin();
  lcdHandler.begin();
  sensorHandler.begin();	
  changePage(PAGE_MAIN);
}

void DishWasher::updateCurrentPage() {
  switch (pageId)
  {
    case PAGE_MAIN:
      updateMenu();
      break;
    case PAGE_SETTINGS:
      updateSettings();
      break;
  }
}

void DishWasher::updateSettings() {
  lcdHandler.DrawCircleBackground(BgImageRightTop::TWO);
  lcdHandler.DrawCircleBackground(BgImageRightBottom::ONE);
  lcdHandler.DrawCircleBackground(BgImageLeftBottom::TWO);
  lcdHandler.DrawCircleBackground(BgImageLeftTop::TWO);
}

void DishWasher::updateMenu() {

  // Draw circle
  if(selection != MENU_QUICKWASH && selection != MENU_COLDWASH) {
    lcdHandler.DrawCircleBackground(BgImageRightTop::TWO);
    lcdHandler.DrawCircleIcon(SmallIconPositionRightTop::TWO_1,SmallIcon::SOAP);
    lcdHandler.DrawCircleIcon(SmallIconPositionRightTop::TWO_2,SmallIcon::SNOWFLAKE);
  } else {
    if(selection == MENU_QUICKWASH) {
      lcdHandler.DrawCircleBackground(BgImageRightTop::TWO_1_SELECTED);
      lcdHandler.DrawCircleIcon(SmallIconPositionRightTop::TWO_1,SmallIconSelected::SOAP);
      lcdHandler.DrawCircleIcon(SmallIconPositionRightTop::TWO_2,SmallIcon::SNOWFLAKE);
    } else {
      lcdHandler.DrawCircleBackground(BgImageRightTop::TWO_2_SELECTED);
      lcdHandler.DrawCircleIcon(SmallIconPositionRightTop::TWO_1,SmallIcon::SOAP);
      lcdHandler.DrawCircleIcon(SmallIconPositionRightTop::TWO_2,SmallIconSelected::SNOWFLAKE);
    }
  }

  if(selection != MENU_POWERWASH) {
    lcdHandler.DrawCircleBackground(BgImageRightBottom::ONE);
    lcdHandler.DrawCircleIcon(SmallIconPositionRightBottom::ONE,SmallIcon::FIRE);
  } else {
    lcdHandler.DrawCircleBackground(BgImageRightBottom::ONE_SELECTED);
    lcdHandler.DrawCircleIcon(SmallIconPositionRightBottom::ONE,SmallIconSelected::FIRE);
  }

  if(selection != MENU_ECOWASH && selection != MENU_HANDWASH) {
    lcdHandler.DrawCircleBackground(BgImageLeftBottom::TWO);
    lcdHandler.DrawCircleIcon(SmallIconPositionLeftBottom::TWO_1,SmallIcon::LEAF);
    lcdHandler.DrawCircleIcon(SmallIconPositionLeftBottom::TWO_2,SmallIcon::CONTROLLER);
  } else {
    if(selection == MENU_ECOWASH) {
      lcdHandler.DrawCircleBackground(BgImageLeftBottom::TWO_1_SELECTED);
      lcdHandler.DrawCircleIcon(SmallIconPositionLeftBottom::TWO_1,SmallIconSelected::LEAF);
      lcdHandler.DrawCircleIcon(SmallIconPositionLeftBottom::TWO_2,SmallIcon::CONTROLLER);
    } else {
      lcdHandler.DrawCircleBackground(BgImageLeftBottom::TWO_2_SELECTED);
      lcdHandler.DrawCircleIcon(SmallIconPositionLeftBottom::TWO_1,SmallIcon::LEAF);
      lcdHandler.DrawCircleIcon(SmallIconPositionLeftBottom::TWO_2,SmallIconSelected::CONTROLLER);
    }
  }

  if(selection != MENU_SETTINGS && selection != MENU_POWEROFF) {
    lcdHandler.DrawCircleBackground(BgImageLeftTop::TWO);
    lcdHandler.DrawCircleIcon(SmallIconPositionLeftTop::TWO_1,SmallIcon::TOOLS);
    lcdHandler.DrawCircleIcon(SmallIconPositionLeftTop::TWO_2,SmallIcon::CABLE);
  } else {
    if(selection == MENU_SETTINGS) {
      lcdHandler.DrawCircleBackground(BgImageLeftTop::TWO_1_SELECTED);
      lcdHandler.DrawCircleIcon(SmallIconPositionLeftTop::TWO_1,SmallIconSelected::TOOLS);
      lcdHandler.DrawCircleIcon(SmallIconPositionLeftTop::TWO_2,SmallIcon::CABLE);
    } else {
      lcdHandler.DrawCircleBackground(BgImageLeftTop::TWO_2_SELECTED);
      lcdHandler.DrawCircleIcon(SmallIconPositionLeftTop::TWO_1,SmallIcon::TOOLS);
      lcdHandler.DrawCircleIcon(SmallIconPositionLeftTop::TWO_2,SmallIconSelected::CABLE);
    }
  }

  // Draw center
  switch (selection) {
    case MENU_NOSELECTED:
      lcdHandler.DrawLargeIcon(LargeIcon::HOME);
      lcdHandler.DrawText(TextPosition::CENTER_TOP, "Valitse");
      lcdHandler.DrawText(TextPosition::CENTER_BOTTOM, "toiminto");
      break;
    case MENU_QUICKWASH: // Fast
      lcdHandler.DrawLargeIcon(LargeIcon::SOAP);
      lcdHandler.DrawText(TextPosition::CENTER_TOP, "Pikapesu");
      lcdHandler.DrawText(TextPosition::CENTER_BOTTOM, "30m");
      break;
    case MENU_COLDWASH: // Cold
      lcdHandler.DrawLargeIcon(LargeIcon::SNOWFLAKE);
      lcdHandler.DrawText(TextPosition::CENTER_TOP, "Kalasia");
      lcdHandler.DrawText(TextPosition::CENTER_BOTTOM, "30m");
      break;
    case MENU_POWERWASH: // Long
      lcdHandler.DrawLargeIcon(LargeIcon::FIRE);
      lcdHandler.DrawText(TextPosition::CENTER_TOP, "Superpesu");
      lcdHandler.DrawText(TextPosition::CENTER_BOTTOM, "1h");
      break;
    case MENU_ECOWASH: // Eco
      lcdHandler.DrawLargeIcon(LargeIcon::LEAF);
      lcdHandler.DrawText(TextPosition::CENTER_TOP, "Ekopesu");
      lcdHandler.DrawText(TextPosition::CENTER_BOTTOM, "30m");
      break;
    case MENU_HANDWASH: // Hand
      lcdHandler.DrawLargeIcon(LargeIcon::CONTROLLER);
      lcdHandler.DrawText(TextPosition::CENTER_TOP, "Manuaali");
      lcdHandler.DrawText(TextPosition::CENTER_BOTTOM, "ohjaus");
      break;
    case MENU_SETTINGS: // Service
      lcdHandler.DrawLargeIcon(LargeIcon::TOOLS);
      lcdHandler.DrawText(TextPosition::CENTER_TOP, "Huolto");
      lcdHandler.DrawText(TextPosition::CENTER_BOTTOM, "valikko");
      break;
    case MENU_POWEROFF: // Power
      lcdHandler.DrawLargeIcon(LargeIcon::CABLE);
      lcdHandler.DrawText(TextPosition::CENTER_TOP, "Sammuta");
      lcdHandler.DrawText(TextPosition::CENTER_BOTTOM, "virta");
      break;
  }

}

void DishWasher::changePage(int newPage) {
  switch (newPage) {

    case PAGE_MAIN:
      selection = MENU_NOSELECTED;
      minSelection = 1;
      maxSelection = 7;
      break;
    
    case PAGE_SETTINGS:
      selection = 1;
      minSelection = 1;
      maxSelection = 2;
      break;
  }
  
  pageId = newPage;
  updateCurrentPage();
}

void DishWasher::loop() {
  quickWashProgram.loop();
  userControl.loop();
  sensorHandler.loop();
  userActions();
}

DishWasher::DishWasher() : quickWashProgram(&relayHandler, &sensorHandler) {
  buttonPressed = true;
}

void DishWasher::userActions() {
  if(userControl.userPress()) {
    if(!buttonPressed) {
      
      switch (pageId) {
        case PAGE_MAIN:
          switch (selection) {

            case MENU_POWEROFF:
              lcdHandler.LcdClear();
              lcdHandler.DrawLargeIcon(LargeIcon::CABLE);
              lcdHandler.DrawText(TextPosition::CENTER_TOP, "Heippa!");
              delay(1000);
              relayHandler.mainPowerOff();
              break; // Selection break
            
            case MENU_SETTINGS:
              changePage(PAGE_SETTINGS);
              break;
          }
          break; // Page break 

        
      }
    }
  }
  else 
  {
    buttonPressed = false;
  }

  if(userControl.userScrollLeft()) {
    
    if(selection > minSelection) {
      selection--;
    } else {
      selection = maxSelection;
    }

    updateCurrentPage();
  }
  if(userControl.userScrollRight()) {

    if(selection<maxSelection) {
      selection++;
    } else {
      selection = minSelection;
    }

    updateCurrentPage();
  }

}