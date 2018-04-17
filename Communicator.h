#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <MCP2515.h>
#include <SPI.h>


class Communicator
{
public:
	Communicator(unsigned long adrsValue);
	~Communicator();
	void SendCommand(uint_8 byteOne, uint_8 byteTwo, uint_8 byteThree, uint_8 byteFour, uint_8 byteFive);
	void SendCommand(uint_8 byteOne, uint_8 byteTwo, uint_8 byteThree, uint_8 byteFour);
	void SendCommand(uint_8 byteOne, uint_8 byteTwo, uint_8 byteThree);
	void SendCommand(uint_8 byteOne, uint_8 byteTwo);

};

#endif