#include "Communicator.h"
#include "WaterModule.h"
WaterModule watermodule;
//0 is receive, 1 is transmit
int mode = 0;
void setup() {
  Serial.begin(9600);
  WaterModule watermodule = WaterModule();
}

void loop() {
  switch (mode)
  {
    case 0:    
      if(watermodule.GetCommunicator()->ReceiveMessage(20, 10))
      {
        watermodule.ProcessMessage();
      }
      break;
    case 1:
      
      break;
    default:
      break;
  }
}
