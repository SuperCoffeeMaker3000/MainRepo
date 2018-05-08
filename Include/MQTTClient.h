#ifndef MQTTSERVER_H
#define MQTTSERVER_H

#include "iMQTTServer.h"

class MQTTSserver : public iMQTTServer
{
public:
	MQTTSserver();
	~MQTTSserver();
	void SendInstruction();
	void Reply();
};

#endif