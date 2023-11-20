// Arduino pin numbers for the joystick
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

// Arduino pin numbers for the stepper motor
#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12

int step_number = 0; // step index for the stepper motor
bool lastDirection; // direction of the last step

void setup() {
  pinMode(SW_pin, INPUT_PULLUP);
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int xValue = analogRead(X_pin);
  int yValue = analogRead(Y_pin);
  
  // Determine the direction based on the X-axis value
  bool direction = xValue < 512; // left
  int speed = map(abs(xValue - 512), 0, 512, 0, 200); // speed is proportional to joystick deflection

  // If the joystick is moved significantly off-center, step the motor
  if (speed > 10) { // add a dead zone to avoid motor noise
    OneStep(direction);
    delay(map(speed, 10, 200, 50, 1)); // speed control
  }

  // Print joystick values for debugging
  Serial.print("X-axis: ");
  Serial.print(xValue);
  Serial.print(" | Y-axis: ");
  Serial.println(yValue);
}

void OneStep(bool dir) {
  // Update direction of the last step if it has changed
  if (lastDirection != dir) {
    step_number = (dir ? 3 : 0); // reset step to 3 if direction changed to left, 0 if to right
    lastDirection = dir;
  }
  
  // Step the motor
  switch (step_number) {
    case 0:
      digitalWrite(STEPPER_PIN_1, HIGH);
      digitalWrite(STEPPER_PIN_2, LOW);
      digitalWrite(STEPPER_PIN_3, LOW);
      digitalWrite(STEPPER_PIN_4, LOW);
      break;
    case 1:
      digitalWrite(STEPPER_PIN_1, LOW);
      digitalWrite(STEPPER_PIN_2, HIGH);
      digitalWrite(STEPPER_PIN_3, LOW);
      digitalWrite(STEPPER_PIN_4, LOW);
      break;
    case 2:
      digitalWrite(STEPPER_PIN_1, LOW);
      digitalWrite(STEPPER_PIN_2, LOW);
      digitalWrite(STEPPER_PIN_3, HIGH);
      digitalWrite(STEPPER_PIN_4, LOW);
      break;
    case 3:
      digitalWrite(STEPPER_PIN_1, LOW);
      digitalWrite(STEPPER_PIN_2, LOW);
      digitalWrite(STEPPER_PIN_3, LOW);
      digitalWrite(STEPPER_PIN_4, HIGH);
      break;
  }
  
  // Increment or decrement the step number based on direction
  step_number = dir ? (step_number - 1) : (step_number + 1);
  if (step_number > 3) {
    step_number = 0;
  } else if (step_number < 0) {
    step_number = 3;
  }
}
