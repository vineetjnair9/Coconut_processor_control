#include <Stepper.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>
#include <Wire.h>
//#include <utility/Adafruit_MS_PWMServoDriver>

//#define actuatorPin 0 // Pin on shield connected to motor controller
#define in1 13
#define in2 12

#define tServoPin 10 // Bottom lead screw
#define cServoPin 9 // Clamp servo

int drillSteps = 200; // Steps per revolution
int meatSteps = 100; //
int drillSpeed = 800; // default speed (RPM)
int meatSpeed = 255;
int PWMopen = 100; // To open the clamps with actuator
int PWMclose = 50; // To close clamps

int drillRev = 20000; // no. of revolutions needed to drill into coconut
int meatRev = 7000; // no. of revolutions needed to scrape off all meat

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); // Create the motor shield object with the default I2C address

// Connect a Stepper motor with 100(?) inBytes per revolution to motor port #2 (M3 and M4)
Adafruit_StepperMotor *drillMotor = AFMS.getStepper(drillSteps, 2);

// Connect a Stepper motor with 200(?) inBytes per revolution to motor port #1 (M1 and M2)
Adafruit_StepperMotor *meatMotor = AFMS.getStepper(meatSteps, 1);

Servo cServo;   // clamp servo
Servo tServo;   // track servo

void setup() {
  // start serial port at 9600 bps
  Serial.begin(9600);

  //pinMode(actuatorPin, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  // Set initial rotation direction for actuator
  //digitalWrite(in1, LOW);
  //digitalWrite(in2, HIGH);

  drillMotor->setSpeed(drillSpeed); // drill motor
  meatMotor->setSpeed(meatSpeed); // meat scraper default speed
  AFMS.begin();
}

void loop() {
  char inByte = '0';
  if (Serial.available()) {
    // get incoming byte
    inByte = Serial.read();
    //cServo.detach();
    //tServo.detach();
  }
 
    if (inByte == '1') { // drilling coconut and moving it forward into drill bit
        tServo.attach(tServoPin);
        tServo.write(0); // clockwise rotation to push coconut into
        drillMotor->step(drillRev, BACKWARD, DOUBLE);

      //   if (Serial.available() > 0) {
      //    tServo.detach();
      //    break;
      //   }
      /*if (Serial.available() > 0) {
        break;
        }*/
    }

    if (inByte == 'c') { // Stop drilling
      tServo.detach();
      drillMotor->step(1, FORWARD, DOUBLE);
    }

    else if (inByte == '2') { // pull coconut out
      tServo.attach(tServoPin); // detach servo to prevent “creeping” effect
      tServo.write(180); // rotation to pull coconut away
      drillMotor->step(drillRev, FORWARD, SINGLE); // counterclockwise opposite rotation to pull out of coconut
      delay(15);
      tServo.detach();
    }

    else if (inByte == '3') { // Drain water
      //cServo.write(90);
      cServo.attach(cServoPin);
      cServo.write(85); // clockwise rotation slowly
      delay(3000); // TO DO: Find exactly how long needed for servo to turn 90 degrees
      cServo.detach(); //
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

    else if (inByte == '8') { // Move Clamps In
      tServo.detach();
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      //analogWrite(actuatorPin, PWMopen);
    }

    else if (inByte == '9') { // Move Clamps Out
      tServo.detach();
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      //analogWrite(actuatorPin, PWMclose);
    }

    else if (inByte == 'a') {  // Meat scraper cut path
      meatMotor->step(meatRev, FORWARD, DOUBLE);
    }

    else if (inByte == 'b') {  // Meat scraper reverse path
      meatMotor->step(meatRev, BACKWARD, SINGLE);
    }
  }


