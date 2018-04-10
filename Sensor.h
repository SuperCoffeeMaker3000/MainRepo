#ifndef SENSOR_H
#define SENSOR_H

#include "iSensor.h"

class Sensor : public iSensor
{
public:
	Sensor();
	~Sensor();
	void GetData();

private:
	int sensorID;
};

#endif