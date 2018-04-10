#ifndef IMQTTSERVER_H
#define IMQTTSERVER_H

#include <string>

class iMQTTServer
{
public:
	~iMQTTServer();
	void SendMessage(std::string message);
	std::string ReceiveMessage();
};

#endif