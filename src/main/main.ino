#include "Motor.h"

void setup(){
  Serial.begin(9600);
  setSpeed();
}

void loop(){
  forward();
}

