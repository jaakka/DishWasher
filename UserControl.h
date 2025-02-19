#ifndef USERCONTROL_H
#define USERCONTROL_H

#define PIN_EncoderLeft 2
#define PIN_EncoderRight 3
#define PIN_EncoderPress A6

class UserControl {
  public:
    void begin();
    void loop();
    bool userScrollRight();
    bool userScrollLeft();
    bool userPress();
  private:  
    int buttonValue;
    int buttonValues[10]; 
    void updateButtonValues(int value);
    int averageButtonValues();
};

#endif