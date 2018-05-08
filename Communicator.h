#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <MCP2515.h>
#include <SPI.h>
#include <stdint.h>


class Communicator
{
public:
	Communicator(unsigned long adrsValue);
	~Communicator();
	void SendCommand(uint8_t byteOne, uint8_t byteTwo, uint8_t byteThree, uint8_t byteFour, uint8_t byteFive);
	void SendCommand(uint8_t byteOne, uint8_t byteTwo, uint8_t byteThree, uint8_t byteFour);
	void SendCommand(uint8_t byteOne, uint8_t byteTwo, uint8_t byteThree);
	void SendCommand(uint8_t byteOne, uint8_t byteTwo);

};

#endif