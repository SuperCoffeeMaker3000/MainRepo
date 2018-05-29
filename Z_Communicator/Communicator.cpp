#include "Communicator.h"

Communicator::Communicator(unsigned long adrsValue)
{
	Serial.begin(9600);
	SPI.setClockDivider(SPI_CLOCK_DIV8);
	can.initCAN(CAN_BAUD_100K);

    msg.isExtendedAdrs = false;
	msg.rtr = false;
	msg.dataLength = 8;
	msg.adrsValue = adrsValue;
}

Communicator::~Communicator()
{	

}

void Communicator::SendCommand(uint8_t byteOne, uint8_t byteTwo, uint8_t byteThree, uint8_t byteFour, uint8_t byteFive)
{
	msg.data[0] = byteOne;  
	msg.data[1] = byteTwo; 
	msg.data[2] = byteThree; 
	msg.data[3] = byteFour;
	msg.data[4] = byteFive;
	
	can.transmitCANMessage(msg, 1000);
	
	return;
}
void Communicator::SendCommand(uint8_t byteOne, uint8_t byteTwo, uint8_t byteThree, uint8_t byteFour)
{
	msg.data[0] = byteOne;  
	msg.data[1] = byteTwo; 
	msg.data[2] = byteThree; 
	msg.data[3] = byteFour;
	
	can.transmitCANMessage(msg, 1000);
	
	return;
}
void Communicator::SendCommand(uint8_t byteOne, uint8_t byteTwo, uint8_t byteThree)
{
	msg.data[0] = byteOne;  
	msg.data[1] = byteTwo; 
	msg.data[2] = byteThree; 
	
	can.transmitCANMessage(msg, 1000);
	
	return;
}
void Communicator::SendCommand(uint8_t byteOne, uint8_t byteTwo)
{
	msg.data[0] = byteOne;  
	msg.data[1] = byteTwo; 
	
	can.transmitCANMessage(msg, 1000);
	
	return;
}
bool Communicator::ReceiveMessage(int firstByte, unsigned long canId)
{
	int i = can.receiveCANMessage(&msg, 1000);
	if(i && (msg.data[0] == firstByte) && msg.adrsValue == canId)
	{
		return true;
	}
	return false;
}