#ifndef CONTROLLERMODULE_H
#define CONTROLLERMODULE_H

class ControllerModule
{
public:
	ControllerModule();
	~ControllerModule();
	int GiveInstruction();
	int BroadCast();
	int SendUpdatesToUI(int option, uint8_t target, uint8_t message, uint8_t module, uint8_t status, uint8_t error, uint8_t availableModules);

private:
	uint8_t byteToSend;
};

#endif