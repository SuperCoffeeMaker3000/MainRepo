#ifndef IVALVE_H
#define IVALVE_H
#include <Servo.h>

class iValve
{

public:


	virtual ~iValve() {};
  virtual Servo;
  virtual int;
  virtual int;
	virtual void OpenValve() = 0;
	virtual void CloseValve() = 0;
};

#endif
