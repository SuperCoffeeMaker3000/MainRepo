#ifndef MODULE_H
#define MODULE_H

#include "iModule.h"

class Module : public iModule
{
public:
	Module();
	~Module();
	void Reply();
	void GiveStatusUpdate();

private:
	string moduleID;
};

#endif