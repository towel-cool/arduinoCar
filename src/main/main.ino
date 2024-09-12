#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

const int servoPos = 0;    // variable to store the servo position
const int buttonPin = 3;
int buttonState = 0;
const int servoPin = 2;

void setup() {
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
  pinMode(buttonPin, INPUT);
  pinMode(servoPin, OUTPUT);
  myservo.write(0);
}

void sweepServo(int servoPos) {
  if (servoPos = 0){
    for (servoPos = 0; servoPos <= 180; servoPos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(servoPos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15ms for the servo to reach the position
    }
  }
  if (servoPos = 0){
    for (servoPos = 180; servoPos >= 0; servoPos -= 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(servoPos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15ms for the servo to reach the position
    }
  }
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    sweepServo(servoPos);
  }
}