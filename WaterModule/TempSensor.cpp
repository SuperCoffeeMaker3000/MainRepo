#include "TempSensor.h"

double Tempsensor::GetData()
{
    double sensorvalue = analogRead(A0);
    double voltage = analogRead(A0) / 204.8;
    double temp = 12.657 * pow(voltage, 2) - 71.883 * voltage + 120.42;
    return temp;
}