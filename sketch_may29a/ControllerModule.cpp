#include "ControllerModule.h"

enum subStates
{
	pouringPowders,
	heating,
	finished
};

enum states
{
	idle,
	makingBeverage
};



enum superStates
{
	running,
	error
};

states state;

superStates superState;

subStates subState;

ControllerModule::ControllerModule()
{
    
  AddressSugarModule  = 0x16;
  AddressCoffeePowder = 0x15;
  AddressChocoPowder  = 0x19;
  AddressMilkPowder   = 0x17;
  AddressWaterModule  = 0x14;
  AddressUiModule   =   0x7ff; //veranderd
  /*
	SugarModule  = 	new Communicator(AddressSugarModule);
	CoffeePowder =	new Communicator(AddressCoffeePowder);
	ChocoPowder  = 	new Communicator(AddressChocoPowder);
	WaterModule  = 	new Communicator(AddressWaterModule);
 */
	UiModule 	 =  new Communicator(AddressUiModule);
  
	//MilkPowder 	 =	new Communicator(AddressMilkPowder);

}

ControllerModule::~ControllerModule()
{
	// nothing to delete here
}

void ControllerModule::test()
{
        while(true){
        Serial.println("hallo");
        if(UiModule->ReceiveMessage(1, 1))
        {
          Serial.println("fix");
        }
        
        delay(10);
      }
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



int ControllerModule::RunMachine()
{
	switch(state)
	{


		case idle:
			//add if command on button pressed here

			
      Serial.println("hallo");
      while(true){
        Serial.println("hallo");
        UiModule->ReceiveMessage(1, 0x7df);
        Serial.println(UiModule->msg.data[0]);
        delay(200);
      }
			  /*while(UiModule->ReceiveMessage(0x0A, AddressUiModule) == true)
			{

    
        Serial.println("it's je boy");
				tempByte = 		UiModule->msg.data[1]; 
				volumeByte = 	UiModule->msg.data[2];

				
				if(tempByte == 0x00)
				{
					state = makingBeverage;
					subState = pouringPowders;
				}else
				{
					state = makingBeverage;
					subState = heating;
				}
        
			}*/

		break;

		case makingBeverage:

			switch(subState)
			{
				case heating:
				//add code to control the boiler
				WaterModule->SendCommand(AddressWaterModule, volumeByte);

				while(WaterModule->ReceiveMessage(0x0A, AddressWaterModule) == true)
				{
					statusByte = WaterModule->msg.data[2];
					if(statusByte == 0x02){
						subState = finished;
					}
				}



				break;

				case finished:
					//add code to deploy water in cup
					UiModule->SendCommand(AddressUiModule, 0x00, 0x0A, 0x02);

					state = idle;

				break;

				case pouringPowders:
					//add code to pour powders
					while(UiModule->ReceiveMessage(0x0A, AddressUiModule) == false)
					{						

						tempByte = UiModule->msg.data[1]; 
						

					}
			break;

			
			//add code to loop through the making beverage process

			}

			
		break;
	}
		

}


/*
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

int ControllerModule::SendUpdatesToController(uint8_t target, uint8_t typeDrank, uint8_t volumeDrink, uint8_t strengthDrink, uint8_t amountSugar, uint8_t amountMelk){

	byteToSend[0] = target;
	byteToSend[1] = typeDrank;
	byteToSend[2] = volumeDrink;
	byteToSend[3] = strengthDrink;
	byteToSend[4] = amountSugar;
	byteToSend[5] = amountMelk;

	return 0;
}

int ControllerModule::SendUpdatesToModules(uint8_t target, uint8_t amount){

	byteToSend[0] = target;

	return 0;
}
*/
