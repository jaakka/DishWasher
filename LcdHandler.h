#ifndef LCDHANDLER_H
#define LCDHANDLER_H

#include <SoftwareSerial.h>

class LcdHandler 
{
    public:
        LcdHandler();
        void begin();
    private:
        SoftwareSerial LcdSerial;
        void LcdHandler::SendLcdCommand(String cmd);
        void UpdateText(int elementId, String txt);
        void LcdClear();
        void UpdateImage(int elementId, int imageId);
};

#endif