#ifndef SUGERMODULE_H
#define SUGERMODULE_H

#include <SPI.h>
#include <MCP2515.h>

#include <arduino.h>
#include "iModule.h";
#include "iValve.h"
#include "Valve.h"

class SugarModule
{
private:
	int mode;
  unsigned long timer; 
  bool timerStarted;
  bool dispenseDelayStarted;
  void dispenseCooldown();

public:
  CANMSG msg;
  MCP2515 can;
  unsigned long controllerID;
	SugarModule();
	~SugarModule();
	bool Dispense(int volume) ; //houden
  bool Receive();
  void Transmit();
  int getMessage();
	iValve* SugarValve;
};

#endif
