#include <Communicator.h>
#include "WaterModule.h"

WaterModule* watermodule;
//0 is receive, 1 is transmit
int mode = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("test");
  watermodule = new WaterModule();
}

void loop() {
  watermodule->UpdatePID();
  switch (mode)
  {
    case 0:
      //watermodule.ProcessMessage();
      mode = 1;
      break;
    case 1:
      //watermodule.GetCommunicator()->SendCommand(CONTROLLER, 0x03);
      mode = 0;
      break;
    default:
      break;
  }
}
