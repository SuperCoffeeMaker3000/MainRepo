#include "TempSensor.h" 
#include "Arduino.h"
 
int Tempsensor::GetData()
{ 
    double sensorvalue = analogRead(SensorPin);
 
    double voltage = analogRead(SensorPin) / 204.8; //voltage from arduino analogRead() goes from 0 to 1023. Voltage actually goes from 0 to 5. So divide by 204.8 
 
    double temp = 12.657 * pow(voltage, 2) - 71.883 * voltage + 120.42;
 
    return temp;
 }
 
