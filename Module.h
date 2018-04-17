#ifndef MODULE_H
#define MODULE_H

#include "iModule.h"

class Module : public iModule
{
public:
	Module(string ModuleID);
	~Module();
	void SendMessage();
	void GiveStatusUpdate();

private:
	string moduleID;
};

#endif