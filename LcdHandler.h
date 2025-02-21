#ifndef LCDHANDLER_H
#define LCDHANDLER_H

#include <SoftwareSerial.h>

class LcdHandler 
{
    public:
        LcdHandler();
        void begin();
        void UpdateText(int elementId, String txt);
    private:
        SoftwareSerial LcdSerial;
        void LcdHandler::SendLcdCommand(String cmd);
        void LcdClear();
        void UpdateImage(int elementId, int imageId);
};

#endif