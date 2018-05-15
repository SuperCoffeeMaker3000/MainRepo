#include "WaterModule.h"
#include "Arduino.h"

WaterModule::WaterModule(string ModuleID)
    : Module(string ModuleID)
{
    tempSensor = TempSensor();
}

void WaterModule::PumpWaterIntoBoiler()
{
    digitalWrite(pumpPin, HIGH);
    //timing
    digitalWrite(pumpPin, LOW);
}

int WaterModule::PumpWaterIntoCup(int cupSize)
{
    switch
        cupSize
        {
        case 1:
            digitalWrite(pumpPin, HIGH);
            //timing for small cup
            digitalWrite(pumpPin, LOW);
            break;

        case 2:
            digitalWrite(pumpPin, HIGH);
            //timing for medium cup
            digitalWrite(pumpPin, LOW);
            break;

        case 3:
            digitalWrite(pumpPin, HIGH);
            //timing for big cup
            digitalWrite(pumpPin, LOW);
            break;

        case default
        {
            //error parameter
            return -1;
        }
    }
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
