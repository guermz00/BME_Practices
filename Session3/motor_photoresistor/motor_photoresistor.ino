// Define pin numbers for the stepper motor
#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12

// Define the input pin for the photoresistor
int sensorPin = A0;
// Define the LED pin
int ledPin = 13;
// Variable to store the value coming from the sensor
int sensorValue = 0;
// Step index for the stepper motor
int step_number = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  digitalWrite(ledPin, HIGH); // Turn on the LED when motor is stepping
  OneStep();
  digitalWrite(ledPin, LOW); // Turn off the LED when motor is not stepping
  
  int delayTime = map(sensorValue, 0, 1023, 10, 1000); // Map sensor value to a delay time
  delay(delayTime); // Delay between steps to control speed

  Serial.println(sensorValue, DEC);
}

void OneStep() {
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
  step_number++;
  if (step_number > 3) {
    step_number = 0;
  }
}
