#ifndef TEMPSENSOR
#define TEMPSENSOR

#include "Sensor.h"

class TempSensor : public Sensor
{
    public:
        double GetData();
    private:
        //analog
        int SensorPin = 0;
};

#endif
