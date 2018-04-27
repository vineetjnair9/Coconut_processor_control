#include <Adafruit_MotorShield.h>
#include <Wire.h>
#define actuatorPin 0 

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(actuatorPin, 100);
}
