#include <TempSensor.h>
#include <WaterModule.h>
Tempsensor tempsensor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  Serial.println(tempsensor.GetData());
  delay(100);
}