#include "Algorithms.h"
#include "Motor.h"
#include "IRSensor.h"
#include "ObjectDetect.h"
#include <stdlib.h>
#include "Stack.h"
#include "lineTrackingSensors.h"
#include "irDetection.h"
#include <Servo.h>

int lastSensorArray[10] = {0,0,0,0,0,0,0,1,1,1};
int sensorArray[10] = {0,0,0,0,0,0,0,1,1,1};
int* IrDetectionArray;
int* trackingArray;
// 0 to 3 = ir sensors
// 4 to 9 = ultrasonics and switches
// order goes front left, front right, back left, back right for ir sensors
// order goes front left, front right, center for ultrasonics and switches
// 0 = object, 1 = no object

// Can we go forward variable
int sensorsGood = 0;

int timeoutLight = 0;

int lowestMid = 999;
int middleSensor = 0;

bool isTracking = false;
bool isLight = false;

Servo servo;
int pos;

int laserPin = 53;

bool shoot() {
  digitalWrite(laserPin, HIGH);
  delay(1000);
  IrDetectionArray = getIrDetectionArray();
  if (IrDetectionArray[0] > 800 && IrDetectionArray[1] > 800 && IrDetectionArray[2] > 800) {
    digitalWrite(laserPin, LOW);
    // indicate();
    pos = 90;
    servo.write(pos);
    return true;
  }
  digitalWrite(laserPin, LOW);
  delay(1000);
  return false;
}

void indicate() {
  swivelLeft();
  delay(300);
  swivelRight();
  delay(300);
  swivelLeft();
  delay(300);
  swivelRight();
  delay(300);
  swivelLeft();
  delay(2000);
}

void setThings() {
  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, LOW);
  servo.attach(50);
  servo.write(90);
}

void turnLeftServo() {
  if (pos < 180) {
    pos = pos + 1;
  }
  servo.write(pos);
}

void turnRightServo() {
  if (pos > 0) {
    pos = pos - 1;
  }
  servo.write(pos);
}

void setSensorArray() {
  int* IR_array = checkGround();
  int* Obj_Det_Array = checkSurroundings();
  trackingArray = getTrackingArray();
  IrDetectionArray = getIrDetectionArray();

  for (int i = 0; i < 4; i++) {
    sensorArray[i] = IR_array[i];
  }
  for (int i = 4; i < 7; i++) {
    sensorArray[i] = Obj_Det_Array[i-4];
  }

  // Serial.print("Ir Detection Array: ");

  // for (int i = 0; i < 3; i++){
  //   Serial.print(IrDetectionArray[i]);
  //   Serial.print(" ");
  // }
  // Serial.print("\n");
}

void move(){
    if (!isTracking && !isLight) {
      // searching state
      for (int i = 0; i < 10; i++)
      {
        if (i < 2 && sensorArray[i] == 0) {
          sensorsGood += 1;
        }  
        else if (i >= 4 && sensorArray[i] == 1) {
          sensorsGood += 1;
        }
      }
      // we can go forward if the front IRs and all the object sensors are good
      if (sensorsGood == 8) {
        forward();
      }
      sensorsGood = 0;
    } else if (isLight) {
      Serial.print(IrDetectionArray[0]);
      Serial.print(" ");
      Serial.print(IrDetectionArray[1]);
      Serial.print(" ");
      Serial.print(IrDetectionArray[2]);
      Serial.println("");
      Serial.println(lowestMid);
      brake();
      
      if (IrDetectionArray[0] < IrDetectionArray[1]) {
        while (lowestMid > middleSensor){
          middleSensor = IrDetectionArray[2];
          //lowestMid = middleSensor;
          IrDetectionArray = getIrDetectionArray();
          delay(15);
          turnLeftServo();
        }
        lowestMid = 999;
      }

      if (IrDetectionArray[0] > IrDetectionArray[1]) {
        while (lowestMid > middleSensor){
          middleSensor = IrDetectionArray[2];
          //lowestMid = middleSensor;
          IrDetectionArray = getIrDetectionArray();
          delay(15);
          turnRightServo();
        }
        lowestMid = 999;
      }

      if (shoot() || (timeoutLight > 15) ) {
        Serial.print("Graa \n");
        isLight = false;
        timeoutLight = 0;
      }

      timeoutLight++;

    } else if (isTracking) {
      if (trackingArray[0] == 1 && trackingArray [1] == 1 && trackingArray[2] == 1) {
        forward();
      }
      else if (trackingArray[0] == 1 && trackingArray [1] == 1 && trackingArray[2] == 0) {
        while (trackingArray[2] != 1 && trackingArray[1] == 0) {
          trackingArray = getTrackingArray();
          swivelLeft();
        }
      }
      else if (trackingArray[0] == 1 && trackingArray [1] == 0 && trackingArray[2] == 1) {
        while (trackingArray[2] != 1 && trackingArray[1] == 0) {
          trackingArray = getTrackingArray();
          swivelLeft();
        }
      }
      else if (trackingArray[0] == 1 && trackingArray [1] == 0 && trackingArray[2] == 0) {
        while (trackingArray[2] != 1 && trackingArray[1] == 0) {
          trackingArray = getTrackingArray();
          swivelLeft();
        }
      }
      else if (trackingArray[0] == 0 && trackingArray [1] == 1 && trackingArray[2] == 1) {
        while (trackingArray[2] != 1 && trackingArray[0] == 0) {
          trackingArray = getTrackingArray();
          swivelRight();
        }
      }
      else if (trackingArray[0] == 0 && trackingArray [1] == 1 && trackingArray[2] == 0) {
        while (trackingArray[2] != 1 && trackingArray[0] == 0) {
          trackingArray = getTrackingArray();
          swivelRight();
        }
      }
      else if (trackingArray[0] == 0 && trackingArray [1] == 0 && trackingArray[2] == 1) {
        forward();
      }
      else if (trackingArray[0] == 0 && trackingArray [1] == 0 && trackingArray[2] == 0) {
        forward();
      }
    }
    // If Flame Sensors Detect IR
    if (IrDetectionArray[0] < 800 || IrDetectionArray[1] < 800 || IrDetectionArray[2] < 800) {
      isLight = true;
      isTracking = false;
    }
    // Line Tracker
    if (trackingArray[0] == 0 || trackingArray[1] == 0) {
      // checks if the robot detects a line
      isTracking = true;
    }

    // IR sensors
    if (sensorArray[0] == 1 || sensorArray[1] == 1){
      // case where either of the front two ir sensors don't detect anything
      // reverse for a bit, until the sensors are detecting the table again
      backward();
      delay(300);

      // then swivel at a random angle
      swivelRight();
      delay(800);
      
      // TURNS OFF TRACKING MODE
      isTracking = false;
      
    } 
    if (sensorArray[2] == 1 || sensorArray[3] == 1) {
      // case where either of the back two ir sensors don't detect anything
      // brake
      brake();

      // go forward a bit
      forward();
    }
    
    // Ultrasonic Sensors
    if ((sensorArray[4] == 0 || sensorArray[5] == 0 || sensorArray[6] == 0) && !isLight) {
      // case where the ultrasonic sensors detect an object infront
      // brake
      brake();
      
      //then swivel at a random angle
      swivelRight();
      delay(800);


      // TURNS OFF TRACKING MODE
      isTracking = false;
      // isLight = false;
      Serial.println("OBJECT DETECTED!! \n");
    }

    // // Switches.   NOT IN USE
    // if (sensorArray[7] == 0 || sensorArray[8] == 0 || sensorArray[9] == 0) {
    //   // case where the front switches detect an object infront
    //   // reverse (enough to make sure we dont hit anything), then swivel at a random angle
    //   backward();
    //   delay(1000);   // TEST THIS NUMBER
      
    //   //then swivel at a random angle
    //   swivelRight();
    //   delay((rand() % 1000) + 500);

    //   // TURNS OFF TRACKING MODE
    //   isTracking = false;
      
    // }
}
