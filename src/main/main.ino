#include "Motor.h"
#include "IRSensor.h"

const int buttonPin = 22;
int buttonState = 0;
bool isOn = false; 

void startControl() {
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH && isOn == false) {
      isOn = true;
      delay(500);
    }
    else if (buttonState == HIGH && isOn == true) 
    {
      isOn = false;
      delay(500);
    }
}

void setup(){
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  setSpeed();
  setupIR();
  startControl();
}

void moveAlgo() {
    int* sensorArray = checkGround();
    
    for (int i = 0; i < 6; i++)
      Serial.print(sensorArray[i]);
    Serial.println();

    if (sensorArray[0] == 0 && sensorArray[1] == 0 && sensorArray[2] == 0 && sensorArray[3] == 0 && sensorArray[4] == 0 && sensorArray[5] == 0) {
      // forward safe
      forward();
    }
    else if (sensorArray[0] == 0 && sensorArray[1] == 1 && sensorArray[2] == 0 && sensorArray[3] == 0 && sensorArray[4] == 0 && sensorArray[5] == 0) {
      // FM unsafe
      backward();
      delay(100);
      leftTurn();
      delay(150);
    }
    else if (sensorArray[0] == 1 && sensorArray[1] == 0 && sensorArray[2] == 0 && sensorArray[3] == 0 && sensorArray[4] == 0 && sensorArray[5] == 0) {
    // FL unsafe
      backward();
      delay(100);
      rightTurn();
      delay(150);
    }
    else if (sensorArray[0] == 0 && sensorArray[1] == 0 && sensorArray[2] == 1 && sensorArray[3] == 0 && sensorArray[4] == 0 && sensorArray[5] == 0) {
      //FR unsafe
      backward();
      delay(100);
      leftTurn();
      delay(150);
    }
    else if (sensorArray[0] == 1 && sensorArray[1] == 1 && sensorArray[2] == 0 && sensorArray[3] == 0 && sensorArray[4] == 0 && sensorArray[5] == 0) {
    // FM, FL unsafe
      backward();
      delay(100);
      rightTurn();
      delay(150);
    }
    else if (sensorArray[0] == 1 && sensorArray[1] == 1 && sensorArray[2] == 0 && sensorArray[3] == 0 && sensorArray[4] == 0 && sensorArray[5] == 0) {
    // FM, FR unsafe
      backward();
      delay(100);
      leftTurn();
      delay(150);
    }
    // TODO:
    // FM FR FL unsafe
    // FR FL unsafe
    // add if back is unsafe for all of these. you could do sub conditionals in each
    // if we dont randomize or come up with a better solution for what to do when front is blocked, there is a chance itll end up in an infinite loop. we cant just go left or right
}

void loop(){
  startControl();

  if (isOn) {
    moveAlgo();
  }
  else 
    brake();
}

