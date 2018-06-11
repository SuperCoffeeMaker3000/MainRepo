
#include "SugarModule.h"

SugarModule::SugarModule()
{
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  can.initCAN(CAN_BAUD_100K);
  can.setCANNormalMode(LOW);
  msg.adrsValue = 0x7df;
  msg.isExtendedAdrs = false;
  msg.rtr = false;
  msg.dataLength = 8;
  SugarValve = new Valve();
  mode = 0;                     //0 ontvangen //1 verzenden
  controllerID = 10;
  timer = millis();
  timerStarted = false;
  dispenseDelayStarted = false;
}

SugarModule::~SugarModule()
{

}

bool SugarModule::Dispense(int volume)
{
  if (timerStarted == false)
  {
    SugarValve->OpenValve();
    timer = millis();
    timerStarted = true;
  }

  while (1)
  {
    switch (volume) {
      case 1:
        if ((millis() - timer) > 1000 && timerStarted)
        {
          if (dispenseDelayStarted == false)
          {
            SugarValve->CloseValve();
            dispenseDelayStarted = true;
          }
          if (dispenseDelayStarted && (millis() - timer) > 2000)
          {
            timerStarted = false;
            dispenseDelayStarted = false;
            return true;
          }
        }
        break;

      case 2:
        if ((millis() - timer) > 2000 && timerStarted)
        {
          Serial.println("in case 2 dispense");
          if (dispenseDelayStarted == false)
          {
            Serial.println("dispenseDelayStarted succes");
            SugarValve->CloseValve();
            dispenseDelayStarted = true;
          }
          if (dispenseDelayStarted && (millis() - timer) > 3000)
          {
            Serial.println("Nieuwe code test");
            timerStarted = false;
            dispenseDelayStarted = false;
            return true;
          }
        }
        break;

      case 3:
        if ((millis() - timer) > 3000 && timerStarted)
        {
          if (dispenseDelayStarted == false)
          {
            SugarValve->CloseValve();
            dispenseDelayStarted = true;
          }
          if (dispenseDelayStarted && (millis() - timer) > 4000)
          {
            timerStarted = false;
            dispenseDelayStarted = false;
            return true;
          }
        }
        break;

      default:
        return false;
    }
  }
}

bool SugarModule::Receive()
{
  int i = can.receiveCANMessage(&msg, 1000);

  if (i && msg.adrsValue == 10 && msg.data[0] == 22)
  {
    Serial.println("Receive true");
    return true;
  }
  return false;
}

void SugarModule::Transmit()
{
  msg.adrsValue = 22;
  msg.isExtendedAdrs = false;
  msg.rtr = false;
  msg.dataLength = 8;

  msg.data[0] = 10;
  msg.data[1] = 3;
  msg.data[2] = 2;

  can.transmitCANMessage(msg, 1000);
}

int SugarModule::getMessage()
{
  return msg.data[1];
}


