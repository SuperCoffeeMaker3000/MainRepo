#include <Communicator.h>

#include "ControllerModule.h"

ControllerModule* control;

void setup() {


  // put your setup code here, to run once:
  control = new ControllerModule();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  control->test();
}
