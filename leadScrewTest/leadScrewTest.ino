#include <Servo.h>
#define tServoPin 9 // Bottom lead screw
Servo tServo;   // track servo

void setup() {
  // put your setup code here, to run once:
  tServo.attach(tServoPin);
  tServo.write(105);
}

void loop() {
  // put your main code here, to run repeatedly:

}
