#ifndef MODULE_H
#define MODULE_H

#include "iModule.h"

class Module : public iModule
{
public:
	Module(string ModuleID);
	~Module();
	void SendMessage(uint8_t target, uint8_t message, uint8_t module, uint8_t status);
	void GiveStatusUpdate(int option, uint8_t targetModule, uint8_t messageType, uint8_t status, uint8_t error, uint8_t module);

private:
	string moduleID;
	uint8_t status;
};

#endif