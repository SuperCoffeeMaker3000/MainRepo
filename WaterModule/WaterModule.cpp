#include <SPI.h>
#include <MCP2515.h>
#include <PID_v1.h>
#include "TempSensor.h"
#include "WaterModule.h"
#include "Arduino.h"

#define smallCupVolume 100
#define mediumCupVolume 200
#define bigCupVolume 300

#define controllerAddress 10

WaterModule::WaterModule(int setpoint)
{
  //settings for the PiD controller
  Setpoint = setpoint;
  //setting that work properly (within overshoot spec) are: kp 0.5 ki 15 kd 2
  //setting that work better (more stable) are: kp 0.5 ki 3 kd 5
  Kp = 0.5;
  Ki = 3;
  Kd = 5;
  PIDController = new PID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
  PIDController->SetMode(AUTOMATIC);
  //address for the canbus
  moduleID = 20;
  //sensor for water temperature
  tempSensor = new TempSensor();
  //first input for the PID controller
  Input = tempSensor->GetData();
  //debug for pid printing, true means printing
  debug = true;
  waterTempReached = false;
  //canbus
  SPI.setClockDivider(SPI_CLOCK_DIV8);

  if (can.initCAN(CAN_BAUD_100K) == 0)
  {
    Serial.println("initCAN() failed");
    while (1);
  }
  if (can.setCANNormalMode(LOW) == 0) //normal mode non single shot
  {
    Serial.println("setCANNormalMode() failed");
    while (1);
  }
}

void WaterModule::PumpWaterIntoBoiler()
{
  digitalWrite(PumpRelayPin, HIGH);
  //timing
  //todo: how long does it take to fill the boiler if it is empty?
  digitalWrite(PumpRelayPin, LOW);
}

int WaterModule::PumpWaterIntoCup(int cupSize)
{
  if (!waterTempReached)
  {
    return -1;
  }
  digitalWrite(PumpRelayPin, HIGH);
  switch (cupSize)
  {
    case 1:
      //timing for small cup = 100 ml
      delay(smallCupVolume / GetPumpSpeed() * 1000);
      break;

    case 2:
      //timing for medium cup
      delay(mediumCupVolume / GetPumpSpeed() * 1000);
      break;

    case 3:
      //timing for big cup
      delay(bigCupVolume / GetPumpSpeed() * 1000);
      break;
    default:
      //error parameter
      return -1;
  }
  digitalWrite(PumpRelayPin, LOW);
  return 1;
}

int WaterModule::ActivateHeater(double PWMvalue)
{
  if (PWMvalue < 0 || PWMvalue > 255)
  {
    return -1;
  }
  //on error return -1;

  digitalWrite(BoilerRelayPin, HIGH);
  //use pwm to set the heater on
  analogWrite(BoilerPulsePin, PWMvalue);
  //on succes return 0;
  return 0;
}

int WaterModule::DeactivateHeater()
{
  digitalWrite(BoilerRelayPin, LOW);
  digitalWrite(BoilerPulsePin, 0);
  return 0;
}

double WaterModule::GetPumpSpeed()
{
  //pump speed was 100ml in 22.5 seconds.
  //=4,444 ml/sec
  return 4.444;
}

int WaterModule::GetHeaterStatus()
{
  return tempSensor->GetData();
}

void WaterModule::ProcessMessage()
{
  int i = can.receiveCANMessage(&msg, 1000);
  if (i && msg.adrsValue == controllerAddress && (msg.data[0] == moduleID))
  {
    int volume = msg.data[1];
    PumpWaterIntoCup(volume);
  }
}

void WaterModule::UpdateWaterTempReached()
{
  int temp = GetHeaterStatus();
  if (temp >= 80)
  {
    waterTempReached = true;
    msg.adrsValue = moduleID;
    msg.isExtendedAdrs = false;
    msg.rtr = false;
    msg.dataLength = 8;
    msg.data[0] = 0x02;
    msg.data[1] = 0x01;
    msg.data[2] = 123;
    msg.data[3] = 0;
    msg.data[4] = 0;
    msg.data[5] = 0;
    msg.data[6] = 0;
    msg.data[7] = 0;
    can.transmitCANMessage(msg, 1000);
  }
}

PID* WaterModule::GetPID()
{
  return PIDController;
}

void WaterModule::UpdatePID()
{
  Input = tempSensor->GetData();
  PIDController->Compute();
  ActivateHeater(Output);
  if (debug)
  {
    Serial.print(Input);
    Serial.print(" ");
    Serial.println(Output);
  }
}

