#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution for your motor

// Pins connected to the ULN2003 driver inputs
int motorPin1 = 8;
int motorPin2 = 9;
int motorPin3 = 10;
int motorPin4 = 11;

Stepper myStepper(stepsPerRevolution, motorPin1, motorPin3, motorPin2, motorPin4); 

void setup() {
  myStepper.setSpeed(60);  // set the speed at 60 rpm
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    int steps = Serial.parseInt();  // read the number of steps to move
    myStepper.step(steps);  // move the motor
  }
}
