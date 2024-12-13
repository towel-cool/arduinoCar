#include "Motor.h"
#include "IRSensor.h"
#include "Algorithms.h"
#include "ObjectDetect.h"
#include "lineTrackingSensors.h"

const int buttonPin = 49;
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
  setTrackingSensors();
  setThings();
}


void loop(){
  startControl();

  if (isOn) {
    setSensorArray();
    move();
  }
  else {
    brake();
  }
}

