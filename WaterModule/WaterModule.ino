
#define SensorPin A0
#include <math.h>

double GetTemp()
{
  double sensorvalue = analogRead(A0);
  double voltage = analogRead(A0) / 204.8;
  double temp = 12.657 * pow(voltage, 2) - 71.883 * voltage + 120.42;
  return temp;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  Serial.println(GetTemp());
  delay(100);
}
