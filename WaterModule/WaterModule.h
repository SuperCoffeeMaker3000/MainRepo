#ifndef WATERMODULE
#define WATERMODULE

#include <Communicator.h>
#include "TempSensor.h"
#include "Arduino.h"

class WaterModule
{
  public:
    WaterModule();

    int GetHeaterStatus();
    double GetPumpSpeed();
    void PumpWaterIntoBoiler();
    int PumpWaterIntoCup(int cupSize);
    int ActivateHeater(int PWMvalue);
    int DeactivateHeater();
    Communicator* GetCommunicator();
    void ProcessMessage();

  private:
    unsigned long moduleID;
    Communicator* communicator;
    TempSensor* tempSensor;
    //digital
    const int BoilerRelayPin = 9;
    const int PumpRelayPin = 8;
    const int BoilerPulsePin = 3;
    const int BoilerTempSensorPin = A0;

};
#endif
