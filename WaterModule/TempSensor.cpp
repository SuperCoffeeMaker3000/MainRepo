#include "TempSensor.h"
#include "Arduino.h"

double TempSensor::GetData()
{
  double sensorvalue = analogRead(SensorPin);
  double voltage = sensorvalue / 204.8; //voltage from arduino analogRead() goes from 0 to 1023. Voltage actually goes from 0 to 5. So divide by 204.8
  double temp = 12.449 * pow(voltage, 2) - 71.362 * voltage + 120.57;
  return temp;
}

