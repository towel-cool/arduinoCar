#include "Motor.h"
#include "IRSensor.h"
#include "Algorithms.h"
#include "ObjectDetect.h"

const int buttonPin = 22;
int buttonState = 0;
bool isOn = false; 

void startControl() {
    buttonState = digitalRead(buttonPin);
    if (buttonState == 1 && isOn == false) {
      Serial.println("turning on");
      isOn = true;
      delay(500);
    }
    else if (buttonState == 1 && isOn == true) 
    {
      Serial.println("turning off");
      isOn = false;
      delay(500);
    }
}

void setup(){
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  setSpeed();
  setupIR();
  setupObjectSensors();
}


void loop(){
  startControl();

  if (isOn) {
    checkIR();
    checkObjects();
    move();
    // int* sensorArray = checkGround();
    // for (int i = 0; i < 6; i++){
    //   Serial.print(sensorArray[i]);
    // }
    // Serial.println();
  }
  else {
    brake();
  }
}

