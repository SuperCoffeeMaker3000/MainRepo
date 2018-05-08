#ifndef IWATERMODULE_H
#define IWATERMODULE_H

class iWaterModule
{
public:
	~iWaterModule();
	void SendMessage(uint8_t target, uint8_t message, uint8_t module, uint8_t status);
};

#endif