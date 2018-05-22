#include "WaterModule.h"
WaterModule watermodule;

void setup() {
  Serial.begin(9600);
  String moduleID = "123";
  WaterModule watermodule = WaterModule();
}

void loop() {
  Serial.println(watermodule.GetHeaterStatus());
  delay(100);
}
