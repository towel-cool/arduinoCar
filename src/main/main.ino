#include "Motor.h"
#include "IRSensor.h"

void setup(){
  Serial.begin(9600);
  setSpeed();
  setupIR();
}

void loop(){
  forward();
  checkGround();
  //int* sensorArray = checkGround();
  //for (int i = 0; i < 6; i++)
  //  Serial.print(sensorArray[i]);
}

