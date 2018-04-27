#include <Stepper.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>
#include <Wire.h>
//#include <utility/Adafruit_MS_PWMServoDriver> 

#define actuatorPin 0 // Pin on shield connected to motor controller
#define in3 1
#define in4 2

#define tServoPin 10 // Bottom lead screw
#define cServoPin 9 // Clamp servo

int drillSteps = 1; // Steps per revolution 
int meatSteps = 1; // 
int drillSpeed = 255; // default speed (RPM)
int meatSpeed = 255; 
int PWMopen = 100; // To open the clamps with actuator
int PWMclose = 50; // To close clamps

int drillRev = 1600; // no. of revolutions needed to drill into coconut
int meatRev = 1600; // no. of revolutions needed to scrape off all meat

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); // Create the motor shield object with the default I2C address

// Connect a Stepper motor with 100(?) inBytes per revolution to motor port #2 (M3 and M4)
Adafruit_StepperMotor *drillMotor = AFMS.getStepper(drillSteps, 1);

// Connect a Stepper motor with 200(?) inBytes per revolution to motor port #1 (M1 and M2)
Adafruit_StepperMotor *meatMotor = AFMS.getStepper(meatSteps, 2);

Servo cServo;   // clamp servo
Servo tServo;   // track servo

void setup() {
  // start serial port at 9600 bps
  Serial.begin(9600);
  
  pinMode(actuatorPin, INPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  // Set initial rotation direction for actuator
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  drillMotor->setSpeed(drillSpeed); // drill motor 
  meatMotor->setSpeed(meatSpeed); // meat scraper default speed
  AFMS.begin();
}

 void loop() {  
  char inByte = '0';
  if (Serial.available() > 0) {
    // get incoming byte
    inByte = Serial.read();
  }
  
  // drilling hole code
  // inByte(#inBytes, direction, inBytetype)  
  // inBytetype = double for higher torque
  
 if (inByte == '1') { // drilling coconut and moving it forward into drill bit
   tServo.attach(tServoPin);
   drillMotor->step(drillRev, FORWARD, DOUBLE); 
   tServo.write(0); // clockwise rotation to push coconut into 
  } // stop drilling

  else if (inByte == '2') { // pull coconut out
    while (true) {
      drillMotor->step(drillRev, BACKWARD, SINGLE); // counterclockwise opposite rotation to pull out of coconut
    }
    tServo.detach(); // detach servo to prevent “creeping” effect
    delay(2000); // wait 2 s before restarting servo
    tServo.write(180); // counterclockwise rotation to pull coconut away
    // This might not be needed, I think motor stops automatically
    // drillMotor.setSpeed(0); // stop drill motor   
    // maybe use MICROinByte for smoother motion?
  }

  else if (inByte == '3') { // Drain water
    cServo.attach(cServoPin);
    cServo.write(120); // clockwise rotation slowly 
    delay(2000); // TO DO: Find exactly how long needed for servo to turn 90 degrees
    cServo.detach(); // stop slightly since servo might lag?
  }

  else if (inByte == '4') { // Move Carriage Forward
    tServo.attach(tServoPin);
    tServo.write(180);
  }
  
  else if (inByte == '5') { // Move Carriage Backward
    tServo.attach(tServoPin);
    tServo.write(0);
  }

  else if (inByte == '6') { // Stop everything
    tServo.detach();
    cServo.detach();
  }

  else if (inByte == '7') { // Saw cutting
    cServo.attach(cServoPin);
    cServo.write(105); // 
  }

  else if (inByte == '8') { // Move Clamps Out
    tServo.detach();
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(actuatorPin, PWMopen);
  }

  else if (inByte == '9') { // Move Clamps In
    tServo.detach();
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(actuatorPin, PWMclose);
  }
  
  else if (inByte == 'a') {  // Meat scraper cut path 
    meatMotor->step(meatRev, FORWARD, SINGLE);  
  }

  else if (inByte == 'b') {  // Meat scraper reverse path 
    meatMotor->step(meatRev, BACKWARD, SINGLE);  
  }
 }
 
