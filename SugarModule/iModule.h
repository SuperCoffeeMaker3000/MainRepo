#ifndef IMODULE_H
#define IMODULE_H

class iModule
{
public:
	virtual ~iModule() {};
	virtual bool Dispense(int volume) = 0;
};

#endif
