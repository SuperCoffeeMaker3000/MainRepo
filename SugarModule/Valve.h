#ifndef VALVE_H
#define VALVE_H

#include "iValve.h"
#include <arduino.h>

class Valve : public iValve
{

  public:
    Valve();
    ~Valve();
    int pos;
    int lastpos;
    Servo myservo;
    void OpenValve();
    void CloseValve();
};

#endif
