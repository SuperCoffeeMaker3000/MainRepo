#ifndef CONTROLLERMODULE_H
#define CONTROLLERMODULE_H

class ControllerModule
{
public:
	ControllerModule();
	~ControllerModule();
	void Exit();
	int GiveInstruction();
	int BroadCast();
};

#endif