#include <Stepper.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>
#include <Wire.h>
//#include <utility/Adafruit_MS_PWMServoDriver> 

Servo myServo;   // Define any servo name
int button1 = 13; // ON/OFF Button overall
int button2 = 12; // Button to turn mechanism ON/OFF after saw 
int actuatorPin = 11; // Pin on shield connected to motor controller
int tServoPin = 10; 
int cServoPin = 9;
int drillSteps = 100; // both of these should be the same for the same motor type right?
int meatSteps = 200; // Steps per revolution
int drillPort = 2; // Ports M3 and M4
int meatPort = 1; // Ports M1 and M2
int drillSpeed = 255; // default speed (rpm)
int meatSpeed = 255; 
int PWMopen = 100; // To open the clamps with actuator
int PWMclose = 20; // To close clamps
int drillRev = 1600; // no. of revolutions needed to drill into coconut
int meatRev = 1600; // no. of revolutions needed to scrape off all meat

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); // Create the motor shield object with the default I2C address
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *drillMotor = AFMS.getStepper(100, 2);
Adafruit_StepperMotor *meatMotor = AFMS.getStepper(200, 1);
Servo cServo;   // clamp servo
Servo tServo;   // track servo

void setup() {
  drillMotor->setSpeed(drillSpeed); // drill motor 
  meatMotor->setSpeed(meatSpeed); // meat scraper default speed
}

 void loop() {

  // drilling hole code
  // step(#steps, direction, steptype)  
  // steptype = double for higher torque
  drillMotor->step(drillRev, BACKWARD, DOUBLE);  
  tServo.attach(tServoPin);

  // May have to adjust these angles to avoid interference w/ clamps while cutting/drilling
  tServo.write(180); // clockwise rotation to push coconut into 
  delay(2000); // rotation duration in ms (how long to reach depth of coconut cutting)
  tServo.detach(); // detach servo to prevent “creeping” effect
  delay(1000); // let the hole become smoooth
  tServo.attach(tServoPin);
  tServo.write(0); //counterclockwise rotation to pull coconut away
  delay(2000); // rotation duration in ms
  tServo.detach(); // detach servo to prevent “creeping” effect

  // This might not be needed, I think motor stops automatically
  // drillMotor.setSpeed(0); // stop drill motor   
  drillMotor->step(drillRev, BACKWARD, SINGLE);
  // maybe use MICROSTEP for smoother motion?

// water draining
  cServo.attach(cServoPin);
  cServo.write(180); // clockwise rotation
  delay(2000); // rotation duration in ms (stop at 180 degrees to drain water)
  cServo.detach(); // detach servo to prevent “creeping” effect 
  delay(2000); // time it'll take to drain water
  delay(5000); // wait for saw to turn on (or include switch case for a switch or such)

// saw cutting  
  tServo.attach(tServoPin); 
  tServo.write(0); // forward direction into saw 
  delay(2000); // move until in the middle of saw (in ms)
  tServo.detach(); // detach servo to prevent “creeping” effect
  cServo.attach(cServoPin);
  cServo.write(0); // counterclockwise rotation, switch if needed the other way
  delay(2000); //rotation speed as it cuts (in ms)
  cServo.detach(); // detach servo to prevent “creeping” effect

// start linear actuator and open coconut
  analogWrite(actuatorPin, PWMopen); //tells motor driver to send extra voltage to open linear actuator

//meat scraper
  tServo.attach(tServoPin); 
  tServo.write(0); //forward direction into meat scraper 
  delay(2000); //move until lined up with meat scraper (in ms)
  tServo.detach(); //detach servo to prevent “creeping” effect
  analogWrite(actuatorPin, PWMclose); // close coconut (linear actuator) 

  meatMotor->step(meatRev, BACKWARD, SINGLE);  
  //meatMotor->setSpeed(0); // stop motor
  analogWrite(actuatorPin, PWMopen); //open coconut
 }
 

