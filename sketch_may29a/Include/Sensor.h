#ifndef SENSOR_H
#define SENSOR_H

#include "iSensor.h"

class Sensor : public iSensor
{
public:
	Sensor();
	~Sensor();
	int GetData();
};

#endif