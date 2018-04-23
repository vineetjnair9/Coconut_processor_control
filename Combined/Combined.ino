#include <Servo.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h" 
Servo myServo   // Define any servo name

//Adafruit_MotorShield AFMS = Adafruit_MotorShield(); // Create the motor shield object with the default I2C address
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
//Adafruit_StepperMotor *myMotor = AFMS.getStepper(100, 2);
//Adafruit_StepperMotor *myMotor1 = AFMS.getStepper(200, 1);

void setup() {
  
  //myservo.attach(10);
  //myservo.write(180); //clockwise rotation
  //delay(2000); //rotation duration in ms
  //myservo.detach(); //detach servo to prevent “creeping” effect
  //delay(500); //short pause
  //myservo.attach(10); //reattach servo to pin 9
  //myservo.write(0); //counterclockwise rotation
  //delay(2000); //rotation duration in ms
  //myservo.detach(); //detach servo to prevent “creeping” effect
  //delay(500); //short pause myservo.attach(9); //reattach servo to pin 9 before looping
  //myServo.attach (10);          // Define the servo signal pins on motor shield
  //Serial.begin(9600);           // set up Serial library at 9600 bps
  
  AFMS.begin();  // create with the default frequency 1.6KHz
    //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
    
  myMotor->setSpeed(255); 
  //myMotor1->setSpeed(50); // 50 rpm   
  myMotor->step(1600, BACKWARD, SINGLE);  
  // myMotor1->step(100, FORWARD, SINGLE);
 }

void loop() 
{  
}
