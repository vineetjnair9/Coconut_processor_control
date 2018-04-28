#include <Wire.h>
int in1 = 13;
int in2 = 12;

void setup() {
  // put your setup code here, to run once:
  //pinMode(actuatorPin, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  // Set initial rotation direction for actuator
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
}

void loop() {
  // put your main code here, to run repeatedly:
    //tServo.detach();
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
//    delay(5000);
//    digitalWrite(in1, LOW);
//    digitalWrite(in2, HIGH);
//    delay(5000);
    //analogWrite(actuatorPin, 50);
}
