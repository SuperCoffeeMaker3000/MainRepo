#include "WaterModule.h"
#include "Arduino.h"

#define smallCupVolume 100
#define mediumCupVolume 200
#define bigCupVolume 300

WaterModule::WaterModule(string ModuleID)
    : Module(string ModuleID)
{
    tempSensor = TempSensor();
}

void WaterModule::PumpWaterIntoBoiler()
{
    digitalWrite(pumpPin, HIGH);
    //timing
    //todo: how long does it take to fill the boiler if it is empty?
    digitalWrite(pumpPin, LOW);
}

int WaterModule::PumpWaterIntoCup(int cupSize)
{
    switch (cupSize)
    {
    case 1:
        digitalWrite(pumpPin, HIGH);
        //timing for small cup = 100 ml
        delay(smallCupVolume * GetPumpSpeed());
        digitalWrite(pumpPin, LOW);
        break;

    case 2:
        digitalWrite(pumpPin, HIGH);
        //timing for medium cup
        delay(mediumCupVolume * GetPumpSpeed());
        digitalWrite(pumpPin, LOW);
        break;

    case 3:
        digitalWrite(pumpPin, HIGH);
        //timing for big cup
        delay(bigCupVolume * GetPumpSpeed());
        digitalWrite(pumpPin, LOW);
        break;
    case default:
        //error parameter
        return -1;
    }
    return 1;
}

int WaterModule::ActivateHeater()
{
    //use pwm to set the heater on

    //on succes return 0;

    //on error return -1;
}

int WaterModule::DeactivateHeater()
{
    digitalWrite(boilerPin, 0);
    return 0;
}

double WaterModule::GetPumpSpeed()
{
    //pump speed was 100ml in 22.5 seconds.
    //=4,444 ml/sec
    return 100/22.5;
}