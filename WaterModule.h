#ifndef WATERMODULE_H
#define WATERMODULE_H

#include "iWaterModule.h"

class WaterModule : public iWaterModule
{
public:
	WaterModule();
	~WaterModule();
	void Reply();
};

#endif