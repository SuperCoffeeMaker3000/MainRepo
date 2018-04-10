#ifndef HEATER_H
#define HEATER_H

#include "iHeater.h"

class Heater : public iHeater
{
public:
	Heater();
	~Heater();
	void Heat();
};

#endif