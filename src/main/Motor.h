#include <AFMotor.h>
#include <Arduino.h>

const int DEFAULT_SPEED = 125;

void setSpeed(int speed = DEFAULT_SPEED);
void forward();
void backward();
void brake();
void leftForward();
void rightForward();
void leftTurn();
void rightTurn();
void leftBrake();
void rightBrake();
void leftBackward();
void rightBackward();
void swivelLeft();
void swivelRight();
void swivelRightAngle(int x);
void swivelLeftAngle(int x);
