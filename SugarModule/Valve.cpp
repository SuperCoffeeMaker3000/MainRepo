#include "Valve.h"

Valve::Valve()
{
  int pos = 0;
  int lastpos = 0;
  myservo.attach(9);
}

Valve::~Valve()
{

}

void Valve::OpenValve()
{
  Serial.println("in Open");
  for (pos = 0; pos <= 180; pos += 1)
  {
    myservo.write(pos);
    lastpos = pos;
  }
  return;
}

void Valve::CloseValve()
{
  Serial.println("in Close");
  for (pos = lastpos; pos >= 0; pos -= 1)
  {
    myservo.write(pos);
  }

  return;
}

