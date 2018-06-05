#ifndef IMQTTSERVER_H
#define IMQTTSERVER_H

class iMQTTServer
{
public:
	~iMQTTServer();
	void SendInstruction();
	void Reply();
};

#endif