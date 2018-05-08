#include "../MQTTClient.h"

void setup(){
  MQTTClient mqttClient;
}

void loop(){
  mqttClient.SendMessage("test");
}
