#include "Algorithms.h"
#include "Motor.h"
#include "IRSensor.h"

bool[] previousFunction = [false,false,false,false];
bool[] availableFunctions = [true, true, true, true];
//[forward, brake, leftSwivel, rightSwivel]

int* sensorArray;
int[] lastIR;

void move(){
  
}

void checkIR(){
  availableFunctions = [true, true, true, true];
  int* sensorArray = checkGround();

  if (sensorArray == lastIR){
    //
    availableFunctions = [false, false, false, false];
    availableFunctions[previous] = true;
  }
  else{
    if (sensroArray[0] == 0){
      availableFunctions[0] = false // cant go forward
      availableFunctions[2] = false // cant leftSwivel
    } 
    else if (sensorArray[1] == 0){
      availableFunctions[0] = false //cant go forward
    }
    else if (sensorArray[2] == 0){
      availableFunctions[0] = false 
      availableFunctions[3] = false //cant right swivel 

    }
    else if (sensorArray[3] == 0){
      availableFunctions[2] = false //cant backwards
      availableFunctions[3] = false //cant swivel left
    }
    else if (sensorArray[4] == 0){
      availableFunctions[2] = false
    }
    else if (sensorArray[5] == 0){
      availableFunctions[2] = false //cant backwards
      availableFunctions[4] = false //cant swivel right
    }
  }
  lastIR = sensorArray;
}