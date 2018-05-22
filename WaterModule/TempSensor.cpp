#include "TempSensor.h"
#include "Arduino.h"

int TempSensor::GetData()
{
  double sensorvalue = analogRead(SensorPin);

  double voltage = analogRead(SensorPin) / 204.8; //voltage from arduino analogRead() goes from 0 to 1023. Voltage actually goes from 0 to 5. So divide by 204.8

  double temp = 11.862 * pow(voltage, 2) - 69.875 * voltage + 121.01;

  return temp;
}

