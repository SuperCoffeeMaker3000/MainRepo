#ifndef VALVE_H
#define VALVE_H

#include "iValve.h"

class Valve : public iValve
{
public:
	Valve();
	~Valve();
	void Open();
	void Close();

private:
	int valveID;
};

#endif