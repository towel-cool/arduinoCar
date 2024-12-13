#include <Arduino.h>

int res4[3] = {0,0,0};

int frSensorReading;
int flSensorReading;
int mSensorReading;

int* getIrDetectionArray() {
  frSensorReading = analogRead(A12); // FR = A12
  delayMicroseconds(10);
  flSensorReading = analogRead(A11); // FL= A11
  delayMicroseconds(10);
  mSensorReading = analogRead(A10);  // M = A10

  res4[0] = flSensorReading;
  res4[1] = frSensorReading;
  res4[2] = mSensorReading;

  return res4;
}