#include <SPI.h>
#include <MCP2515.h>
#include "ControllerModule.h"

enum subStates
{
  pouringPowders,
  pouringWater,
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
  Serial.println("Creating controller");

  //CANBUS
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  if (can.initCAN(CAN_BAUD_100K) == 0)
  {
    Serial.println("initCAN() failed");
    while (1);
  }
  if (can.setCANNormalMode(LOW) == 0) //normal mode non single shot
  {
    Serial.println("setCANNormalMode() failed");
    while (1);
  }
  msg.isExtendedAdrs = false;
  msg.rtr = false;
  msg.dataLength = 8;

  //This module's address
  Address = 10;
  //ADDRESSES
  AddressSugarModule  = 22;
  AddressCoffeePowder = 21;
  AddressChocoPowder  = 25;
  AddressMilkModule   = 23;
  AddressSoupPowder   = 24;
  AddressWaterModule  = 20;
  AddressUiModule   =   11;

  state = idle;
  Serial.println("Controller created");
}

ControllerModule::~ControllerModule()
{
  // nothing to delete here
}

int ControllerModule::GiveInstruction()
{

  return 0;
}

int ControllerModule::BroadCast()
{
  // TO DO

  return 0;
}

int ControllerModule::RunMachine()
{
  switch (state)
  {
    case idle:
      {
        Serial.println("RunMachine::idle");
        //add if command on button pressed here
        Serial.println("Receiving the can message");
        int i = can.receiveCANMessage(&msg, 1000);
        Serial.println("Received message");
        //test case
        i = 1;
        msg.adrsValue = AddressUiModule;
        msg.data[0] = Address;
        msg.data[1] = 0;
        msg.data[2] = 0;
        msg.data[3] = 0;
        msg.data[4] = 2;
        msg.data[5] = 2;
        //end test case
        if (i && msg.adrsValue == AddressUiModule && msg.data[0] == Address)
        {
          Serial.println("Setting message for further instructions");
          /*
             koffie = 0x00
             thee = 0x01
             choco = 0x02
             soep = 0x03
          */
          typeDrankByte = msg.data[1];
          volumeByte = msg.data[2];
          sterkteByte = msg.data[3];
          sterkteSuikerByte = msg.data[4];
          sterkteMelkByte = msg.data[5];
          Serial.print("typeDrankByte = ");
          Serial.println(typeDrankByte);
          switch (typeDrankByte)
          {
            //Koffie
            case 0:
              {
                state = makingBeverage;
                subState = pouringPowders;
                break;
              }
            //Thee
            case 1:
              {
                state = makingBeverage;
                subState = pouringWater;
                break;
              }
            //Chocomel
            case 2:
              {
                state = makingBeverage;
                subState = pouringPowders;
                break;
              }
            //Soep
            case 3:
              {
                state = makingBeverage;
                subState = pouringPowders;
                break;
              }
            default:
              {
                break;
              }
          }
        }
      }
    case makingBeverage:
      {
        Serial.println("RunMachine::makingBeverage");
        switch (subState)
        {
          case pouringWater:
            {
              Serial.println("RunMachine::substate = pouringWater");
              msg.adrsValue = Address;
              msg.isExtendedAdrs = false;
              msg.rtr = false;
              msg.dataLength = 8;
              msg.data[0] = AddressWaterModule;
              msg.data[1] = volumeByte;
              can.transmitCANMessage(msg, 1000);
              delay(100);
              break;
            }
          case finished:
            {
              //add code to deploy water in cup
              state = idle;
              break;
            }
          case pouringPowders:
            {
              Serial.println("RunMachine::substate = pouringPowders");
              Serial.print("RunMachine::substate typeDrankByte = ");
              Serial.println(typeDrankByte);
              //coffee
              if (typeDrankByte == 0)
              {
                //first pour sugar
                if (sterkteSuikerByte != 0)
                {
                  msg.adrsValue = Address;
                  msg.data[0] = AddressSugarModule;
                  msg.data[1] = sterkteSuikerByte;
                  //sending the sugar command
                  can.transmitCANMessage(msg, 1000);
                  Serial.println(msg.adrsValue);
                  Serial.println(msg.data[0]);
                  Serial.println(msg.data[1]);
                  Serial.println("RunMachine::substate = pouringPowders, message sent");
                  delay(100);
                  //receiving the ack
                  Serial.println("Waiting for ACK");
                  bool receivedAck = false;
                  while (!receivedAck)
                  {
                    int i = can.receiveCANMessage(&msg, 1000);
                    if (i && msg.adrsValue == AddressSugarModule && msg.data[0] == Address)
                    {
                      if (msg.data[1] == 3 && msg.data[2] == 2)
                      {
                        receivedAck = true;
                        Serial.println("Received ACK");
                      }
                    }
                  }
                }

                //then pour milk
                if (sterkteMelkByte != 0)
                {
                  msg.adrsValue = Address;
                  msg.data[0] = AddressMilkModule;
                  msg.data[1] = sterkteMelkByte;
                  //sending the milk command
                  can.transmitCANMessage(msg, 1000);
                  Serial.println(msg.adrsValue);
                  Serial.println(msg.data[0]);
                  Serial.println(msg.data[1]);
                  delay(100);
                  Serial.println("RunMachine::substate = pouringPowders, message sent");
                  //receiving the ack
                  Serial.println("Waiting for ACK");
                  bool receivedAck = false;
                  while (!receivedAck)
                  {
                    int i = can.receiveCANMessage(&msg, 1000);
                    if (i && msg.adrsValue == AddressMilkModule && msg.data[0] == Address)
                    {
                      //this means ack
                      if (msg.data[1] == 3 && msg.data[2] == 2)
                      {
                        receivedAck = true;
                        Serial.println("Received ACK");
                      }
                    }
                  }
                }

                //then puur the coffee
                msg.adrsValue = Address;
                msg.data[0] = AddressCoffeePowder;
                msg.data[1] = sterkteByte;
                //sending the milk command
                can.transmitCANMessage(msg, 1000);
                Serial.println(msg.adrsValue);
                Serial.println(msg.data[0]);
                Serial.println(msg.data[1]);
                delay(100);
                Serial.println("RunMachine::substate = pouringPowders, message sent");
                //receiving the ack
                Serial.println("Waiting for ACK");
                bool receivedAck = false;
                while (!receivedAck)
                {
                  int i = can.receiveCANMessage(&msg, 1000);
                  if (i && msg.adrsValue == AddressCoffeePowder && msg.data[0] == Address)
                  {
                    //this means ack
                    if (msg.data[1] == 3 && msg.data[2] == 2)
                    {
                      receivedAck = true;
                      Serial.println("Received ACK");
                    }
                  }
                }
              }

              //choco
              else if (typeDrankByte == 0x02)
              {
                msg.data[0] = AddressChocoPowder;
              }
              //soup
              else if (typeDrankByte == 0x03)
              {
                msg.data[0] = AddressSoupPowder;
              }
              break;
            }
        }
        subState = pouringWater;
      }
      break;
  }
  return 0;
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
