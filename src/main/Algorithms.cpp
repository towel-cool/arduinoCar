#include "Algorithms.h"
#include "Motor.h"
#include "IRSensor.h"
#include "ObjectDetect.h"
#include <stdlib.h>
#include "Stack.h"
#include "lineTrackingSensors.h"

int lastSensorArray[10] = {0,0,0,0,0,0,0,1,1,1};
int sensorArray[10] = {0,0,0,0,0,0,0,1,1,1};
int* trackingArray[3];
// 0 to 3 = ir sensors
// 4 to 9 = ultrasonics and switches
// order goes front left, front right, back left, back right for ir sensors
// order goes front left, front right, center for ultrasonics and switches
// 0 = object, 1 = no object

// Can we go forward variable
int sensorsGood = 0;

bool isTracking = false;

void setSensorArray() {
  int* IR_array = checkGround();
  int* Obj_Det_Array = checkSurroundings();
  trackingArray = getTrackingArray();

  for (int i = 0; i < 4; i++) {
    sensorArray[i] = IR_array[i];
  }
  for (int i = 4; i < 10; i++) {
    sensorArray[i] = Obj_Det_Array[i-4];
  }

  //Print the sensor array
  // for (int i = 0; i < 10; i++){
  //   Serial.print(sensorArray[i]);
  //   Serial.print(" ");
  // }
  // Serial.print("\n");
}

void move(){
    if (!isTracking) {
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
        sensorsGood = 0;
      } 

    } else if (isTracking) {
      // line tracking state
      if (trackingArray[0] == 1 && trackingArray[1] == 1)
      {
        swivelRight();
        delay(50);  
      }

      // GO FORWARD
      forward();

      if (trackingArray[2] == 1) {
        // move forward when the middle sensors detects line
        // check middle if line ends
        forward();
      }

      if (trackingArray[0] == 1) {
        // swivel left
        while (trackingArray[2] != 1) {
          swivelRight(); // TEST THIS SPEED, MAKE NEW FUNCTION IF NEEDED
        }
        // brake(); if needed
      }

      if (trackingArray[1] == 1) {
        // swivel right
        while (trackingArray[2] != 1) {
          swivelLeft(); // TEST THIS SPEED, MAKE NEW FUNCTION IF NEEDED
        }
        // brake(); if needed
      }

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
      delay(50);

      // then swivel at a random angle
      swivelRight();
      delay((rand() % 200) + 50);
      
      // TURNS OFF TRACKING MODE
      isTracking = false;
      
    } 
    if (sensorArray[2] == 1 || sensorArray[3] == 1) {
      // case where either of the back two ir sensors don't detect anything
      // brake
      brake();

      // go forward a bit
      forward();
      delay(50);
    }
    
    // Ultrasonic Sensors
    if (sensorArray[4] == 0 || sensorArray[5] == 0 || sensorArray[6] == 0) {
      // case where the ultrasonic sensors detect an object infront
      // brake
      brake();
      
      //then swivel at a random angle
      swivelRight();
      delay((rand() % 200) + 50);


      // TURNS OFF TRACKING MODE
      isTracking = false;
    }

    // Switches
    if (sensorArray[7] == 0 || sensorArray[8] == 0 || sensorArray[9] == 0) {
      // case where the front switches detect an object infront
      // reverse (enough to make sure we dont hit anything), then swivel at a random angle
      backward();
      delay(200);   // TEST THIS NUMBER
      
      //then swivel at a random angle
      swivelRight();
      delay((rand() % 200) + 50);

      // TURNS OFF TRACKING MODE
      isTracking = false;
    }
}
