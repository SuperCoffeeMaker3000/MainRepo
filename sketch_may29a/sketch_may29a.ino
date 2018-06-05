#include <Communicator.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include "PubSubClient.h"
#include "ControllerModule.h"

char* ssid;
char* mqttUser;
char* mqttPass;

char* mqttClientId;
char* buttonTopic;

WiFiClient* Client1;

IPAddress* server;
PubSubClient* mqttClient;

int wifiStatus;

char* currentMessage;
ControllerModule* control;

void setup() {


  // put your setup code here, to run once:
  control = new ControllerModule();

  //WiFi part:
  ssid = "12connect";
  mqttUser = "i339762_martijnbooij";
  mqttPass = "Rtd1Ss44uHGLNq";

  wifiStatus = WL_IDLE_STATUS;

  Client1 = new WiFiClient();

  server = new IPAddress(145, 85, 4, 91);

  mqttClient = new PubSubClient(*Client1);

  mqttClientId = "Genuino101-";
  buttonTopic = "public/i339762_martijnbooij/";
  mqttInit();
}

void connectWifi()
{
  wifiStatus = WiFi.begin(ssid);
}

void connectMqtt()
{
  mqttClient->connect((char*) mqttClientId, mqttUser, mqttPass);
}

void mqttInit() {
  uint8_t mac[6];
  WiFi.macAddress(mac);

  connectWifi();

  mqttClient->setServer(server, 1883);
  connectMqtt();

  mqttClient->subscribe("public/i339762_martijnbooij/");

  mqttClient->setCallback(callback);
}

void callback(char* topic, byte* payload, unsigned int length)
{
  char* temp;

  for (int i = 0; i < length; i++)
  {
    temp[i] = char(payload[i]);
  }

  currentMessage = temp;
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(currentMessage);
  //control->test();
  if (wifiStatus != WL_CONNECTED)
    connectWifi();

  while (!mqttClient->connected())
    connectMqtt();

  Serial.println("Sending and receiving...");
  mqttClient->publish(buttonTopic, "hoi");
  mqttClient->loop();
}
