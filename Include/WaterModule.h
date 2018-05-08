#ifndef WATERMODULE_H
#define WATERMODULE_H

#include "iWaterModule.h"

class WaterModule : public iWaterModule
{
public:
	WaterModule();
	~WaterModule();
	void SendMessage(uint8_t target, uint8_t message, uint8_t module, uint8_t status);

private:
	uint8_t status;
};

#endif