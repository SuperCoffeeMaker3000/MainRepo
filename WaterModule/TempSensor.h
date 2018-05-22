#ifndef TEMPSENSOR
#define TEMPSENSOR

class TempSensor : public Sensor
{
    public:
        int GetData();
    private:
        //analog
        int SensorPin = 0;
};

#endif