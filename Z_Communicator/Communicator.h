#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <SPI.h>
#include <MCP2515.h>
#include <stdint.h>


class Communicator
{
public:
	Communicator(unsigned long adrsValue);
	~Communicator();
	CANMSG msg;
	MCP2515 can;
	void SendCommand(uint8_t byteOne, uint8_t byteTwo, uint8_t byteThree, uint8_t byteFour, uint8_t byteFive);
	void SendCommand(uint8_t byteOne, uint8_t byteTwo, uint8_t byteThree, uint8_t byteFour);
	void SendCommand(uint8_t byteOne, uint8_t byteTwo, uint8_t byteThree);
	void SendCommand(uint8_t byteOne, uint8_t byteTwo);
	bool ReceiveMessage(int firstByte, unsigned long canId);

};

#endif