#ifndef MQTTSERVER_H
#define MQTTSERVER_H

#include "WiFi/WiFi.h"
#include "WiFi/WiFiClient.h"
#include "WiFi/WiFiServer.h"
#include "WiFi/WiFiUdp.h"
#include "PubSubClient.h"

#define WiFiSSID "12connect" 

#define mqttUser "i339322_coffeemaker"
#define mqttPass "Tsp57WQQmFRZmX"
#define publishTopic "public/i339322_coffeemaker/"
#define subscribeTopic "public/i339322_coffeemaker/#"

class MQTTClient
{
private:
	IPAddress* server;
	WiFiClient* client;
	PubSubClient* mqttClient;
	int wifiStatus;
	int mqttStatus;

	int MQTTClient::connectMqtt();
public:
	MQTTClient();
	~MQTTClient();
	void SendMessage(std::string message);
	std::string ReceiveMessage();
	int GetMQTTStatus();
	int GetWifiStatus();
};

#endif