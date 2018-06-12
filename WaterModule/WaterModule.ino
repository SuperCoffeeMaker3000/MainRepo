#include  <MCP2515.h>
#include  "WaterModule.h"

#define setpoint 15

WaterModule* watermodule;
//0 is receive, 1 is transmit
int mode = 0;

void setup() {
  Serial.begin(9600);
  watermodule = new WaterModule(setpoint);
}

void loop() {
  watermodule->UpdatePID();
  watermodule->UpdateWaterTempReached();
  watermodule->ProcessMessage();
}
