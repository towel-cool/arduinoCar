#include "Algorithms.h"
#include "Motor.h"
#include "IRSensor.h"
#include <stdlib.h>
#include "Stack.h"


int previousFunctionIndex = 0;
bool availableFunctions[4] = {true, true, true, true};
//[forward, backwards, leftSwivel, rightSwivel]

int* sensorArray;
int lastIR[6] = {0, 0, 0, 0, 0, 0};

int functionCounter = 0;

Stack<int> possibleFunctions;

void move(){
  // set certain numbers to pick between based on availableFunctions array
  // randomly pick
  // based

  Serial.print("Available Functions: ");
  for (int i = 0; i < 4; i++){
    Serial.print(availableFunctions[i]);
  Serial.println(" ");
  }

  for (int i = 0; i < 4; i++) {
    if (availableFunctions[i] == true)
      possibleFunctions.push(i);
  }

  //Serial.print("Possible Functions");
  for (int i = 0; i < 4; i++){
    //Serial.print(possibleFunctions.get(i));
  //Serial.println(" ");
  }
  //Serial.print("Possible Functions Length: ");
  //Serial.println(possibleFunctions.length());
  int chosenIndex = (rand() % (possibleFunctions.length()));
  int chosenFunctionIndex = possibleFunctions.get(chosenIndex);

  if (chosenFunctionIndex == previousFunctionIndex) {
    functionCounter += 1;
  }
  else {
    functionCounter = 0;
  }

  Serial.print("function counter");
  Serial.println(functionCounter);
  Serial.print("possible functions length");
  Serial.println(possibleFunctions.length());

  if (functionCounter > 30 && chosenFunctionIndex != 1) {
    chosenFunctionIndex = 0;
  }
  else {
    previousFunctionIndex = chosenFunctionIndex;
  }

  if (possibleFunctions.length() > 0) {
      //Serial.print("Chosen Function: ");
      //Serial.println(chosenFunctionIndex);

      switch(chosenFunctionIndex) {
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
}

void checkIR(){
  //Serial.print("Available: ");
  //Serial.println();
  for (int i = 0; i < 4; i++){
    //Serial.print(availableFunctions[i]);
    //Serial.print(" - > ");
    availableFunctions[i] = true;
    //Serial.print(availableFunctions[i]);
    //Serial.println(", ");

}
  int* sensorArray = checkGround();

  //Serial.print("Sensor array: ");
  for (int i = 0; i < 6; i++) {
    //Serial.print(sensorArray[i]);
  }
  //Serial.print(" -> ");
  for (int i = 0; i < 6; i++) {
    //Serial.print(lastIR[i]);
  }
  //Serial.println(" ");

  if (sensorArray[0] == lastIR[0] && sensorArray[1] == lastIR[1] && sensorArray[2] == lastIR[2] && sensorArray[3] == lastIR[3] && sensorArray[4] == lastIR[4] && sensorArray[5] == lastIR[5]){
    //if nothings changed do same
    for (int i = 0; i < 4; i++)
      availableFunctions[i] = false;
    availableFunctions[previousFunctionIndex] = true;
  }
  else{
    // if (sensorArray[0] == 0 && sensorArray[1] == 0 && sensorArray[2] == 0 && sensorArray[3] == 0 && sensorArray[4] == 0 && sensorArray[5] == 0) {
    //   availableFunctions[2] = false;
    //   availableFunctions[3] = false; 
    //   return;
    // }
    if (sensorArray[0] == 1){
      availableFunctions[0] = false; // cant go forward
      availableFunctions[3] = false; // cant leftSwivel
    } 
    if (sensorArray[1] == 1){
      availableFunctions[0] = false; //cant go forward
    }
    if (sensorArray[2] == 1){
      availableFunctions[0] = false; 
      availableFunctions[2] = false; //cant right swivel 
    }
    if (sensorArray[3] == 1){
      availableFunctions[1] = false; //cant backwards
      availableFunctions[2] = false; //cant swivel left
    }
    if (sensorArray[4] == 1){
      //availableFunctions[1] = false; //cant go back
    }
    if (sensorArray[5] == 1){
      availableFunctions[1] = false; //cant backwards
      availableFunctions[3] = false; //cant swivel right
    }
  }
  //Serial.print("last ir: ");
  for (int i = 0; i < 6; i++) {
    //Serial.print(lastIR[i]);
    lastIR[i] = sensorArray[i];
    //Serial.print(" -> ");
    //Serial.print(lastIR[i]);
    //Serial.println(", ");
  }
}
