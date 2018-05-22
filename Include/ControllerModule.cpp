#include "ControllerModule.h"
#include "Communicator.h"

enum states
{
	idle,
	makingBeverage,
	askingForMilkAndSugar,
	pouringPowders,
	heating,
	pouringWater
};
enum superStates
{
	running,
	error
};

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



int runMachine()
{
	switch(states)
		case idle:
			//add if command on button pressed here

		break;

		case makingBeverage:

			//add code to loop through the making beverage process

		break;

		case askingForMilkAndSugar:
			//add code to show choices on UI

		break;

		case pouringPowders:
			//add code to pour powders
		break;

		case heating:
			//add code to control the boiler
		break;

		case pouringWater:
			//add code to deploy water in cup

		break;

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

int SendUpdatesToController(uint8_t target, uint8_t typeDrank, uint8_t volumeDrink, uint8_t strengthDrink, uint8_t amountSugar, uint8_t amountMelk){

	byteToSend[0] = target;
	byteToSend[1] = typeDrank;
	byteToSend[2] = volumeDrink;
	byteToSend[3] = strengthDrink;
	byteToSend[4] = amountSugar;
	byteToSend[5] = amountMelk;

	return 0;
}

int SendUpdatesToModules(uint8_t target, uint8_t amount){

	byteToSend[0] = target;

	return 0;
}
