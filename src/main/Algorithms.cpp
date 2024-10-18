#include "Algorithms.h"
#include "Motor.h"
#include "IRSensor.h"
#include "ObjectDetect.h"
#include <stdlib.h>
#include "Stack.h"

bool availableFunctions[4] = {true, true, true, true};
//[forward, backwards, leftSwivel, rightSwivel]

int lastSensorArray[8] = {0,0,0,0,0,0,0,0};
int sensorArray[8] = {0,0,0,0,0,0,0,0};
// 0 to 3 = ir sensors
// 4 to 7 = ultrasonics and switches
// order goes front left, front right, back left, back right
// 0 = object, 1 = no object

int previousFunctionIndex = 0;
int functionCounter = 0;

Stack<int> possibleFunctions;

void setSensorArray() {
  int* IR_array = checkGround();
  int* Obj_Det_Array = checkSurroundings();

  for (int i = 0; i < 4; i++) {
    sensorArray[i] = IR_array[i];
  }
  for (int i = 4; i < 8; i++) {
    sensorArray[i] = Obj_Det_Array[i-4];
  }

  //Print the sensor array
  for (int i = 0; i < 8; i++){
    Serial.print(sensorArray[i]);
    Serial.print(" ");
  }
  Serial.print("\n");
}

void move(){
    for (int i = 0; i < 4; i++) {
      availableFunctions[i] = true;
    }

    // IR sensors
    if (sensorArray[0] == 1){
      availableFunctions[0] = false; // cant go forward
      availableFunctions[3] = false; // cant leftSwivel
    } 
    if (sensorArray[1] == 1){
      availableFunctions[0] = false; 
      availableFunctions[2] = false; //cant right swivel 
    }
    if (sensorArray[2] == 1){
      availableFunctions[1] = false; //cant backwards
      availableFunctions[2] = false; //cant swivel left
    }
    if (sensorArray[3] == 1){
      availableFunctions[1] = false; //cant backwards
      availableFunctions[3] = false; //cant swivel right
    }
    
    // Ultrasonic Sensors
    if (sensorArray[4] == 0){
      availableFunctions[0] = false;
      availableFunctions[3] = false;
    } 
    if (sensorArray[5] == 0){
      availableFunctions[0] = false;
      availableFunctions[2] = false;
    }

    // Switches
    if (sensorArray[6] == 0){
      availableFunctions[0] = false;
      availableFunctions[2] = false;
    }
    if (sensorArray[7] == 0){
      availableFunctions[0] = false;
      availableFunctions[3] = false;
    }

    for (int i = 0; i < 4; i++) {
      Serial.print(availableFunctions[i]);
      Serial.print(" ");
    }
    Serial.println("\n");

    // this needs to be done before we push the available functions on the stack
    if (sensorArray[0] == lastSensorArray[0] && sensorArray[1] == lastSensorArray[1] && sensorArray[2] == lastSensorArray[2] && sensorArray[3] == lastSensorArray[3] && sensorArray[4] == lastSensorArray[4] && sensorArray[5] == lastSensorArray[5] && sensorArray[6] == lastSensorArray[6] && sensorArray[7] == lastSensorArray[7]) {
      //if nothings changed do same
      for (int i = 0; i < 4; i++) {
        availableFunctions[i] = false;
      }
      availableFunctions[previousFunctionIndex] = true;
    }

    for (int i = 0; i < 4; i++) {
      if (availableFunctions[i] == true) {
        possibleFunctions.push(i);
      }
    }

    int chosenIndex = (rand() % (possibleFunctions.length()));
    int chosenFunctionIndex = possibleFunctions.get(chosenIndex);

    if (chosenFunctionIndex == previousFunctionIndex) {
      functionCounter += 1;
    } else {
      functionCounter = 0;
    }

    if (functionCounter > 20 && chosenFunctionIndex != 1) {
      chosenFunctionIndex = 0;
    } else {
      previousFunctionIndex = chosenFunctionIndex;
    }

    if (possibleFunctions.length() > 0) {
      switch (chosenFunctionIndex) {
        case 0:
          forward();
          Serial.println("forward");
          break;
        case 1:
          backward();
          Serial.println("backward");
          break;
        case 2:
          swivelLeft();
          Serial.println("left swivel");
          break;
        case 3:
          swivelRight();
          Serial.println("right swivel");
          break;
        default:
          break;
      }
    }
    possibleFunctions.clear();

    for (int i = 0; i < 8; i++) {
      lastSensorArray[i] = sensorArray[i];
    }
}