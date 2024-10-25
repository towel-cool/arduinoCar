#include <AFMotor.h>
#include <Arduino.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

// We move too fast. Trying 80 instead of 100.
const int DEFAULT_SPEED = 80;

// Per Wheel Speed Equalization
const int FL_OFFSET = 0;
const int FR_OFFSET = 0;
const int BL_OFFSET = 0;
const int BR_OFFSET = 0;

AF_DCMotor& leftFront = motor2;
AF_DCMotor& leftBack = motor3;
AF_DCMotor& rightFront = motor1;
AF_DCMotor& rightBack = motor4;

void setSpeed(int speed = DEFAULT_SPEED) {
  leftFront.setSpeed(speed + FL_OFFSET);
  leftBack.setSpeed(speed + BL_OFFSET);
  rightFront.setSpeed(speed + FR_OFFSET);
  rightBack.setSpeed(speed + BR_OFFSET);
}

void setLeftSpeed(int x){
  leftFront.setSpeed(speed + FL_OFFSET);
  leftBack.setSpeed(speed + BL_OFFSET);
}

void setRightSpeed(int x){
  rightFront.setSpeed(speed + FR_OFFSET);
  rightBack.setSpeed(speed + BR_OFFSET);
}

void brake() {
  leftBack.run(RELEASE);
  rightBack.run(RELEASE);
  leftFront.run(RELEASE);
  rightFront.run(RELEASE);
  setSpeed();
}
void forward() {
  setSpeed();
  leftFront.run(FORWARD);
  leftBack.run(FORWARD);
  rightFront.run(FORWARD);
  rightBack.run(FORWARD);
}
void backward() {
  setSpeed();
  leftFront.run(BACKWARD);
  leftBack.run(BACKWARD);
  rightFront.run(BACKWARD);
  rightBack.run(BACKWARD);
}

// LEFT RIGHT SETTERS
void leftForward() {
  leftFront.run(FORWARD);
  leftBack.run(FORWARD);
}
void rightForward() {
  rightFront.run(FORWARD);
  rightBack.run(FORWARD);
}
void leftBrake() {
  leftFront.run(RELEASE);
  leftBack.run(RELEASE);
}
void rightBrake() {
  rightFront.run(RELEASE);
  rightBack.run(RELEASE);

}
void leftBackward() {
  leftFront.run(BACKWARD);
  leftBack.run(BACKWARD);
}
void rightBackward() {
  rightFront.run(BACKWARD);
  rightBack.run(BACKWARD);
}
// COMPLEX
void leftTurn() {
  leftBrake();
  rightForward();
}
void rightTurn() {
  rightBrake();
  leftForward();
}
void swivelStop(){
  // where to set how much a car will swivel
  delay(1000);
  brake();
}

// Had an offset of 20 before
void swivelLeft() {
  setLeftSpeed(80);
  setRightSpeed(80);
  leftBackward();
  rightForward();
  
}

// Had an offset of 20 before
void swivelRight() {
  setLeftSpeed(80);
  setRightSpeed(80);
  leftForward();
  rightBackward();
}

void swivelLeftAngle(int x) {
  swivelLeft();
  delay(x);
  setSpeed();
  
}
void swivelRightAngle(int x) {
  setLeftSpeed(200);
  setRightSpeed(200);
  swivelRight();
  delay(x);
  setSpeed();
}

// WTF is this for?!?!
int speed(int percent) {
  return map(percent, 0, 200, 0, 255);
}