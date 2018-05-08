#include "WaterModule.h"

WaterModule::WaterModule()
{

}

WaterModule::~WaterModule()
{
	// nothing to delete here
}

void WaterModule::SendMessage(uint8_t target, uint8_t message, uint8_t module, uint8_t status)
{
	byteToSend[0] = target;
	byteToSend[1] = message;
	byteToSend[2] = module;
	byteToSend[3] = status;

	// TO DO: send here
}