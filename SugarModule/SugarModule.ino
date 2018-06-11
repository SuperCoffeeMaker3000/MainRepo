#include "SugarModule.h"

SugarModule* sugarModule;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("CARRIED BY THIJS");
    Serial.println("IT'S A THIJS THING");
  sugarModule = new SugarModule();
}

void loop() {
  // put your main code here, to run repeatedly:

  if (sugarModule->Receive())
  {
    Serial.println("Proceed into dispensing");
    if (sugarModule->Dispense(sugarModule->getMessage()))
    {
      Serial.println("Procedure complete");
      sugarModule->Transmit();
    }
  }

}


