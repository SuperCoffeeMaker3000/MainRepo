#ifndef WATERMODULE
#define WATERMODULE

class WaterModule : public Module
{
  public:
    WaterModule(string ModuleID);
    int GetHeaterStatus();

  private:
    void PumpWaterIntoBoiler();
    int PumpWaterIntoCup(int cupSize);
    int ActivateHeater();
    int DeactivateHeater();

    TempSensor tempSensor;
    //digital
    int boilerPin = 3;
    int pumpPin = 4;
}
#endif