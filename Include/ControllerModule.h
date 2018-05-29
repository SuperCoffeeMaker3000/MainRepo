#ifndef CONTROLLERMODULE_H
#define CONTROLLERMODULE_H

class ControllerModule
{
public:
	ControllerModule();
	~ControllerModule();
	int GiveInstruction();
	int BroadCast();
	int SendUpdatesToUI(uint8_t option, uint8_t target, uint8_t message, uint8_t module, uint8_t status, uint8_t error, uint8_t availableModules);
	int SendUpdatesToController(uint8_t target, uint8_t typeDrank, uint8_t volumeDrink, uint8_t strengthDrink, uint8_t amountSugar, uint8_t amountMelk);
	int SendUpdatesToModules(uint8_t target, uint8_t amount);
	int dispense(unsigned long id, uint8_t volume);

private:
	uint8_t byteToSend;
	unsigned long AddressSugarModule;
	unsigned long AddressCoffeePowder;
	unsigned long AddressChocoPowder;
	unsigned long AddressWaterModule;
	unsigned long AddressUiModule;
	unsigned long AddressMilkPowder;
	Communicator* SugarModule;
	Communicator* CoffeePowder;
	Communicator* ChocoPowder;
	Communicator* WaterModule;
	Communicator* UiModule;
	Communicator* MilkPowder;
}

#endif