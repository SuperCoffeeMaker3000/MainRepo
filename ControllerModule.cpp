#include "ControllerModule.h"

ControllerModule::ControllerModule()
{

}

ControllerModule::~ControllerModule()
{
	// nothing to delete here
}

void ControllerModule::Exit()
{
}

int ControllerModule::GiveInstruction()
{
	return 0;
}

int ControllerModule::BroadCast()
{
	return 0;
}

int ControllerModule::SendUpdatesToUI(int option, uint8_t target, uint8_t message, uint8_t module, uint8_t status, uint8_t error, uint8_t availableModules)
{
	switch (option)
	{
	case 1:
		// give status update
		byteToSend[0] = target;
		byteToSend[1] = message;
		byteToSend[2] = module;
		byteToSend[3] = status;

		// send here
		break;

	case 2:
		// give error update
		byteToSend[0] = target;
		byteToSend[1] = message;
		byteToSend[2] = error;

		// send here
		break;

	case 3:
		// give available modules
		byteToSend[0] = target;
		byteToSend[1] = message;
		byteToSend[2] = availableModules;

		// send here
		break;

	default:
		// nothing to do here
		break;
	}

	return 0;
}