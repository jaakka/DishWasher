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
  updateMenu();
}

void DishWasher::updateMenu() {

  if(menuPos != 1 && menuPos != 2) {
    lcdHandler.DrawCircleBackground(BgImageRightTop::TWO);
    lcdHandler.DrawCircleIcon(SmallIconPositionRightTop::TWO_1,SmallIcon::SOAP);
    lcdHandler.DrawCircleIcon(SmallIconPositionRightTop::TWO_1,SmallIcon::SNOWFLAKE);
  } else {
    if(menuPos == 1) {
      lcdHandler.DrawCircleBackground(BgImageRightTop::TWO_1_SELECTED);
      lcdHandler.DrawCircleIcon(SmallIconPositionRightTop::TWO_1,SmallIconSelected::SOAP);
      lcdHandler.DrawCircleIcon(SmallIconPositionRightTop::TWO_1,SmallIcon::SNOWFLAKE);
    } else {
      lcdHandler.DrawCircleBackground(BgImageRightTop::TWO_2_SELECTED);
      lcdHandler.DrawCircleIcon(SmallIconPositionRightTop::TWO_1,SmallIcon::SOAP);
      lcdHandler.DrawCircleIcon(SmallIconPositionRightTop::TWO_1,SmallIconSelected::SNOWFLAKE);
    }
  }

  if(menuPos != 3) {
    lcdHandler.DrawCircleBackground(BgImageRightBottom::ONE);
    lcdHandler.DrawCircleIcon(SmallIconPositionRightBottom::ONE,SmallIcon::FIRE);
  } else {
    lcdHandler.DrawCircleBackground(BgImageRightBottom::ONE_SELECTED);
    lcdHandler.DrawCircleIcon(SmallIconPositionRightBottom::ONE,SmallIconSelected::FIRE);
  }

  if(menuPos != 4 && menuPos != 5) {
    lcdHandler.DrawCircleBackground(BgImageLeftBottom::TWO);
    lcdHandler.DrawCircleIcon(SmallIconPositionLeftBottom::TWO_1,SmallIcon::LEAF);
    lcdHandler.DrawCircleIcon(SmallIconPositionLeftBottom::TWO_2,SmallIcon::CONTROLLER);
  } else {
    if(menuPos == 4) {
      lcdHandler.DrawCircleBackground(BgImageLeftBottom::TWO_1_SELECTED);
      lcdHandler.DrawCircleIcon(SmallIconPositionLeftBottom::TWO_1,SmallIconSelected::LEAF);
      lcdHandler.DrawCircleIcon(SmallIconPositionLeftBottom::TWO_2,SmallIcon::CONTROLLER);
    } else {
      lcdHandler.DrawCircleBackground(BgImageLeftBottom::TWO_2_SELECTED);
      lcdHandler.DrawCircleIcon(SmallIconPositionLeftBottom::TWO_1,SmallIcon::LEAF);
      lcdHandler.DrawCircleIcon(SmallIconPositionLeftBottom::TWO_2,SmallIconSelected::CONTROLLER);
    }
  }

  if(menuPos != 6 && menuPos != 7) {
    lcdHandler.DrawCircleBackground(BgImageLeftTop::TWO);
    lcdHandler.DrawCircleIcon(SmallIconPositionLeftTop::TWO_1,SmallIcon::TOOLS);
    lcdHandler.DrawCircleIcon(SmallIconPositionLeftTop::TWO_2,SmallIcon::CABLE);
  } else {
    if(menuPos == 6) {
      lcdHandler.DrawCircleBackground(BgImageLeftTop::TWO_1_SELECTED);
      lcdHandler.DrawCircleIcon(SmallIconPositionLeftTop::TWO_1,SmallIconSelected::TOOLS);
      lcdHandler.DrawCircleIcon(SmallIconPositionLeftTop::TWO_2,SmallIcon::CABLE);
    } else {
      lcdHandler.DrawCircleBackground(BgImageLeftTop::TWO_2_SELECTED);
      lcdHandler.DrawCircleIcon(SmallIconPositionLeftTop::TWO_1,SmallIcon::TOOLS);
      lcdHandler.DrawCircleIcon(SmallIconPositionLeftTop::TWO_2,SmallIconSelected::CABLE);
    }
  }

  switch (menuPos) {
    case 0: // Nothing selected
      lcdHandler.DrawLargeIcon(LargeIcon::HOME);
      lcdHandler.DrawText(TextPosition::CENTER_TOP, "Valitse");
      lcdHandler.DrawText(TextPosition::CENTER_BOTTOM, "toiminto");
      break;
    case 1: // Fast
      lcdHandler.DrawLargeIcon(LargeIcon::SOAP);
      lcdHandler.DrawText(TextPosition::CENTER_TOP, "Pikapesu");
      lcdHandler.DrawText(TextPosition::CENTER_BOTTOM, "30m");
      break;
    case 2: // Cold
      lcdHandler.DrawLargeIcon(LargeIcon::SNOWFLAKE);
      lcdHandler.DrawText(TextPosition::CENTER_TOP, "Kalasia");
      lcdHandler.DrawText(TextPosition::CENTER_BOTTOM, "30m");
      break;
    case 3: // Long
      lcdHandler.DrawLargeIcon(LargeIcon::FIRE);
      lcdHandler.DrawText(TextPosition::CENTER_TOP, "Superpesu");
      lcdHandler.DrawText(TextPosition::CENTER_BOTTOM, "1h");
      break;
    case 4: // Eco
      lcdHandler.DrawLargeIcon(LargeIcon::LEAF);
      lcdHandler.DrawText(TextPosition::CENTER_TOP, "Ekopesu");
      lcdHandler.DrawText(TextPosition::CENTER_BOTTOM, "30m");
      break;
    case 5: // Hand
      lcdHandler.DrawLargeIcon(LargeIcon::CONTROLLER);
      lcdHandler.DrawText(TextPosition::CENTER_TOP, "Manuaali");
      lcdHandler.DrawText(TextPosition::CENTER_BOTTOM, "ohjaus");
      break;
    case 6: // Service
      lcdHandler.DrawLargeIcon(LargeIcon::TOOLS);
      lcdHandler.DrawText(TextPosition::CENTER_TOP, "Huolto");
      lcdHandler.DrawText(TextPosition::CENTER_BOTTOM, "valikko");
      break;
    case 7: // Power
      lcdHandler.DrawLargeIcon(LargeIcon::CABLE);
      lcdHandler.DrawText(TextPosition::CENTER_TOP, "Sammuta");
      lcdHandler.DrawText(TextPosition::CENTER_BOTTOM, "virta");
      break;
  }

}

void DishWasher::loop() {
  userControl.loop();
  powerControl();
}

DishWasher::DishWasher() {
  buttonPressed = true;
}

void DishWasher::powerControl() {
  if(userControl.userPress()) {
    if(!buttonPressed) {
      switch (menuPos) {
        case 7:
          lcdHandler.LcdClear();
          lcdHandler.DrawLargeIcon(LargeIcon::CABLE);
          lcdHandler.DrawText(TextPosition::CENTER_TOP, "Heippa!");
          delay(1000);
          relayHandler.mainPowerOff();
          break;
      }
    }
  }
  else 
  {
    buttonPressed = false;
  }

  if(userControl.userScrollLeft()) {
    Serial.println("vasen");
    if(menuPos>1){menuPos--;}else{menuPos = 7;}
    updateMenu();
  }
  if(userControl.userScrollRight()) {
    Serial.println("right");
    if(menuPos<7){menuPos++;}else{menuPos = 1;}
    updateMenu();
  }

}