#ifndef WATERMODULE
#define WATERMODULE

#include <MCP2515.h>
#include <PID_v1.h>
#include "TempSensor.h"
#include "Arduino.h"

class WaterModule
{
  public:
    //const
    WaterModule(int setpoint);
    //controller
    PID* GetPID();
    void UpdatePID();
    //tempsensor
    int GetHeaterStatus();
    //pump
    double GetPumpSpeed();
    void PumpWaterIntoBoiler();
    int PumpWaterIntoCup(int cupSize);
    //heater
    int ActivateHeater(double temperature);
    int DeactivateHeater();
    void UpdateWaterTempReached();
    //canbus
    void ProcessMessage();

  private:
    //controller
    PID* PIDController;
    double Setpoint, Input, Output;
    double Kp = .5, Ki = 15, Kd = 0;
    bool waterTempReached;
    //canbus
    CANMSG msg;
    MCP2515 can;
    unsigned long moduleID;
    //sensor
    TempSensor* tempSensor;
    //digital
    const int BoilerRelayPin = 9;
    const int PumpRelayPin = 8;
    const int BoilerPulsePin = 3;
    //debug
    bool debug;
};
#endif
