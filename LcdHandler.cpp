#include "LcdHandler.h"
#include "Wiring.h"
#include <Arduino.h>

LcdHandler::LcdHandler() : LcdSerial(LCD_RX, LCD_TX) {
  LcdSerial.begin(9600);
}

void LcdHandler::begin() {
  LcdClear();
  Serial.println("LCD initialized");
  UpdateText(0,"Pikapesu");
  UpdateText(1,"1t 30m"); 
}

void LcdHandler::SendLcdCommand(String cmd)
{
  LcdSerial.print(cmd); // Oletetaan, että t0 on tekstikentän ID
  LcdSerial.write(0xFF); // Komentoon lisätään tarvittavat päättymismerkit
  LcdSerial.write(0xFF);
  LcdSerial.write(0xFF);
}

void LcdHandler::UpdateText(int elementId, String txt)
{
  SendLcdCommand("t"+String(elementId)+".txt=\""+String(txt)+"\"");
}

void LcdHandler::UpdateImage(int elementId, int imageId)
{
  SendLcdCommand("p"+String(elementId)+".pic="+String(imageId));
}

void LcdHandler::LcdClear()
{
  UpdateImage(2, 65);
  UpdateImage(3, 64);
  UpdateImage(4, 63);
  UpdateImage(5, 62);
}