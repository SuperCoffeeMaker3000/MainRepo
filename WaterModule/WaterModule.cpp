#include <Communicator.h>
#include <PID_v1.h>
#include "TempSensor.h"
#include "WaterModule.h"
#include "Arduino.h"

#define smallCupVolume 100
#define mediumCupVolume 200
#define bigCupVolume 300

WaterModule::WaterModule()
{
  //settings for the PID controller
  Setpoint = 70;
  Kp = 0.5;
  Ki = 15;
  Kd = 0;
  PIDController = new PID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
  PIDController->SetMode(AUTOMATIC);
  //address for the canbus
  unsigned long address = 20;
  //canbus communicator
  communicator = new Communicator(address);
  //sensor for water temperature
  tempSensor = new TempSensor();
  //first input for the PID controller
  Input = tempSensor->GetData();
  //debug for pid printing, true means printing
  debug = true;
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
  digitalWrite(PumpRelayPin, HIGH);
  Serial.println("lol");
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
      Serial.println(bigCupVolume * GetPumpSpeed());
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

Communicator* WaterModule::GetCommunicator()
{
  return communicator;
}

void WaterModule::ProcessMessage()
{
  if (communicator->ReceiveMessage(20, 10))
  {
    int volume = communicator->msg.data[1];
    PumpWaterIntoCup(volume);
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

