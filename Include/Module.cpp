#include "Module.h"

Module::Module(string ModuleID)
{
	moduleID = ModuleID;
}

Module::~Module()
{
	// nothing to delete here
}

void Module::SendMessage(uint8_t target, uint8_t message, uint8_t module, uint8_t status)
{
	byteToSend[0] = target;
	byteToSend[1] = message;
	byteToSend[2] = module;
	byteToSend[3] = status;

	// TO DO: send here
}

int Module::GiveStatusUpdate(int option, uint8_t targetModule, uint8_t messageType, uint8_t status, uint8_t error, uint8_t module)
{
	switch (option)
	{
	case 1:
		// give status update
		byteToSend[0] = targetModule;
		byteToSend[1] = messageType;
		byteToSend[2] = status;

		// TO DO: send here
		break;

	case 2:
		// give error update
		byteToSend[0] = targetModule;
		byteToSend[1] = '255';
		byteToSend[2] = module;

		// TO DO: send here
		break;

	case 3:
		// give available modules
		byteToSend[0] = targetModule;
		byteToSend[1] = messageType;
		byteToSend[2] = error;

		// TO DO: send here
		break;

	default:
		// nothing to do here
		break;
	}

	return 0;
}