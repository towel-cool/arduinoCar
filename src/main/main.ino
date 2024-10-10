#include "Motor.h"
#include "IRSensor.h"
#include "Algorithms.h"
#include "ObjectDetect.h"
#include <Servo.h>

const int buttonPin = 22;
int buttonState = 0;
bool isOn = false; 

Servo myservo;

int pos = 0;

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
  myservo.attach(51);
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

    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
  else {
    brake();
  }
}

