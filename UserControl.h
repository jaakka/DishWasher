#ifndef USERCONTROL_H
#define USERCONTROL_H

class UserControl {
  public:
    void begin();
    void loop();
    bool userScrollRight();
    bool userScrollLeft();
    bool userPress();
};

#endif