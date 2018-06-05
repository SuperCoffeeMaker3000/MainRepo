#include <Communicator.h>


Communicator* communicator;

 
void setup() {
  // put your setup code here, to run once:
  communicator = new Communicator(25);
  //sugarModule = new SugarModule(); 
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //sugarModule->SugarModuleCommunicator->ReceiveMessage(sugarModule->controllerID,10);

  while(1)
  {
    
    if(communicator->ReceiveMessage(100,100)){
      Serial.println("ben er");
    }
    Serial.println(communicator->msg.data[0]);
    Serial.println(communicator->msg.adrsValue);
    delay(100);
  }
}
