#include <AFMotor.h>
#include <Arduino.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

AF_DCMotor& leftFront = motor4;
AF_DCMotor& leftBack = motor1;
AF_DCMotor& rightFront = motor3;
AF_DCMotor& rightBack = motor2;

void setSpeed() {
  int speed = 200;
  leftFront.setSpeed(speed);
  leftBack.setSpeed(speed);
  rightFront.setSpeed(speed);
  rightBack.setSpeed(speed);
}

void brake() {
  leftBack.run(RELEASE);
  rightBack.run(RELEASE);
  leftFront.run(RELEASE);
  rightFront.run(RELEASE);
  setSpeed();
}
void forward() {
  leftFront.run(FORWARD);
  leftBack.run(FORWARD);
  rightFront.run(FORWARD);
  rightBack.run(FORWARD);
}
void backward() {
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

void swivelLeft() {
  leftBackward();
  rightForward();
  
}
void swivelRight() {
  leftForward();
  rightBackward();
}

void swivelLeftAngle() {
  swivelLeft();
  swivelStop();
  
}
void swivelRightAngle() {
  swivelRight();
  swivelStop();
}


int speed(int percent) {
  return map(percent, 0, 200, 0, 255);
}