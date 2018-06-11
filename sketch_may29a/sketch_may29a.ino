#include "ControllerModule.h"

ControllerModule* control;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  control = new ControllerModule();

}

void loop() {
  // put your main code here, to run repeatedly:
  control->RunMachine();
}
