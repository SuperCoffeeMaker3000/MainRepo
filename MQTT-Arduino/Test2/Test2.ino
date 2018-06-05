#include "/home/timojansen/Documents/MainRepo/MQTT-Arduino/MQTTClient.h"

void setup(){
  MQTTClient mqttClient;
}

void loop(){
  if(mqttClient.GetWifiStatus == WL_CONNECTED){
    if(mqttClient.GetMQTTStatus == 1){
      mqttClient.SendMessage("test");
    }
  }
}


