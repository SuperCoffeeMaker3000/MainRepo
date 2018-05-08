#include "MQTTClient.h"

MQTTClient::MQTTClient(){
	server = new IPAddress(145,85,4,91);
	wifiStatus = WL_IDLE_STATUS;
	client = new WiFiClient();
	mqttClient = new PubSubClient(*client);

	wifiStatus = connectWifi();
	mqttClient.setServer(server, 1883)
	mqttStatus = connectMqtt();
}

MQTTClient::~MQTTClient(){
	delete server, client, mqttClient;
	server = NULL;
	client = NULL;
	mqttClient = NULL;
}

int MQTTClient::GetMQTTStatus(){
	return mqttStatus;
}

int mqttClient::GetWifiStatus(){
	return wifiStatus;
}

// Call to connect to the MQTT server
int MQTTClient::connectMqtt(){
  if(!mqttClient.connect("CoffeeMaker", mqttUser, mqttPass))
      {
        //FAILURE
        return -1;
      }
      else
      {
        //SUCCESS
        return 1;
      }
}

int MQTTClient::connectWifi(){
	return WiFi.begin(WiFiSSID);
}

void MQTTClient::SendMessage(std::string message){
	mqttClient.publish(mqttTopic, message.c_str());
}

std::string ReceiveMessage(){
	return "test";
}
