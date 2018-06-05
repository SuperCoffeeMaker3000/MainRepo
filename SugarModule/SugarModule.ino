#include <Communicator.h>


Communicator* communicator;

 
void setup() {
  // put your setup code here, to run once:
  communicator = new Communicator(100);
  //sugarModule = new SugarModule(); 
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //sugarModule->SugarModuleCommunicator->ReceiveMessage(sugarModule->controllerID,10);

  while(1)
  {
    communicator->SendCommand(100,100);
    Serial.println(communicator->msg.data[1]);
    delay(100);
  }
}
