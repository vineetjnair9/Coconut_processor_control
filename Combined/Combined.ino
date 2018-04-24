#include <Stepper.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>
#include <Wire.h>
//#include <utility/Adafruit_MS_PWMServoDriver> 

Servo myServo;   // Define any servo name

// 2 Continuous rotation servos
// 2 Steppers
// Motor controller for actuator
// Motor shields
// 1 Linear actuator

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); // Create the motor shield object with the default I2C address
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(100, 2);
Adafruit_StepperMotor *myMotor1 = AFMS.getStepper(200, 1);

void setup() {
  
 Adafruit_MotorShield AFMS = Adafruit_MotorShield(); // Create the motor shield object with the default I2C address
 Servo cServo;   // clamp servo
 Servo tServo;   // track servo
  
// drilling hole code
  myMotor->setSpeed(255); // drill motor   
  myMotor->step(1600, BACKWARD, SINGLE);  
  tServo.attach(10);
  tServo.write(180); //clockwise rotation to push coconut into 
  delay(2000); //rotation duration in ms (how long to reach depth of coconut cutting)
  tServo.detach(); //detach servo to prevent “creeping” effect
  delay(1000); // let the hole become smoooth
  tServo.attach(10);
  tServo.write(0); //counterclockwise rotation to pull coconut away
  delay(2000); //rotation duration in ms
  tServo.detach(); //detach servo to prevent “creeping” effect
  myMotor->setSpeed(0); // stop drill motor   
  myMotor->step(1600, BACKWARD, SINGLE);  

// water draining
  cServo.attach(10);
  cServo.write(180); //clockwise rotation
  delay(2000); //rotation duration in ms (stop at 180 degrees to drain water)
  cServo.detach(); //detach servo to prevent “creeping” effect 
  delay(2000); // time it'll take to drain water
  
  delay(5000); // wait for saw to turn on (or include switch case for a switch or such)

// saw cutting  
  tServo.attach(10); 
  tServo.write(0); //forward direction into saw 
  delay(2000); //move until in the middle of saw (in ms)
  tServo.detach(); //detach servo to prevent “creeping” effect
  cServo.attach(10);
  cServo.write(0); //counterclockwise rotation, switch if needed the other way
  delay(2000); //rotation speed as it cuts (in ms)
  cServo.detach(); //detach servo to prevent “creeping” effect

// start linear actuator and open coconut
  analogWrite(pin, value); //tells motor driver to send extra voltage to open linear actuator

//meat scraper
  tServo.attach(10); 
  tServo.write(0); //forward direction into meat scraper 
  delay(2000); //move until lined up with meat scraper (in ms)
  tServo.detach(); //detach servo to prevent “creeping” effect
  analogWrite(pin, value); //close coconut

  myMotor2->setSpeed(255); // meat scraper motor start
  myMotor2->step(1600, BACKWARD, SINGLE);  
  myMotor2->setSpeed(0); // stop motor
  analogWrite(pin, value); //open coconut
 }
