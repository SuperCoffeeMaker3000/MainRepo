#ifndef TEMPSENSOR
#define TEMPSENSOR

#include "ISensor.h"

class TempSensor : public Sensor
{
    public:
        double GetData();
    private:
        //analog
        int SensorPin = 0;
}


#endif