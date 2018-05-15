#include "ControllerModule.h"
#include "Communicator.h"



ControllerModule::ControllerModule()
{
	SugarModule = 	new Communicator(AddressSugarModule);
	CoffeePowder =	new Communicator(AddressCoffeePowder);
	ChocoPowder = 	new Communicator(AddressChocoPowder);
	WaterModule = 	new Communicator(AddressWaterModule);
	
	AddressSugarModule	= 0x7df;
	AddressCoffeePowder	= 0x7de;
	AddressChocoPowder	= 0x7dd;
	AddressWaterModule	= 0x7dc;
}

ControllerModule::~ControllerModule()
{
	// nothing to delete here
}

int ControllerModule::GiveInstruction()
{
	// TO DO

	return 0;
}

int ControllerModule::BroadCast()
{
	// TO DO

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

		com.SendCommand(byteToSend);

		// send here
		break;

	case 2:
		// give error update
		byteToSend[0] = target;
		byteToSend[1] = message;
		byteToSend[2] = error;

		com.SendCommand(byteToSend);
		// send here
		break;

	case 3:
		// give available modules
		byteToSend[0] = target;
		byteToSend[1] = message;
		byteToSend[2] = availableModules;

		com.SendCommand(byteToSend);
		// send here
		break;

	default:
		// nothing to do here
		break;
	}

	return 0;
}



