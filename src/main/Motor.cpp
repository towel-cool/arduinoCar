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
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  setSpeed();
}
void forward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
void backward() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

// LEFT RIGHT SETTERS
void leftForward() {
  motor1.run(FORWARD);
  motor4.run(FORWARD);
}
void rightForward() {
  motor2.run(FORWARD);
  motor3.run(FORWARD);
}
void leftBrake() {
}
void rightBrake() {}
void leftBackwards() {}
void rightBackwards() {}

// COMPLEX
void leftTurn() {
  leftBrake();
  rightForward();
}
void rightTurn() {
  rightBrake();
  leftForward();
}


void swivelLeft() {}
void swivelRight() {}

int speed(int percent) {
  return map(percent, 0, 200, 0, 255);
}