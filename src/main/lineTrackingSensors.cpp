#include <Arduino.h>

int pinL = 40;
int isObsL = HIGH;                                                                       
int pinR = 43;
int isObsR = HIGH;
int pinM = 41;
int isObsM = HIGH;

int res3[3] = {0,0,0};

void setTrackingSensors() {
    pinMode(pinL, INPUT);
    pinMode(pinR, INPUT);
    pinMode(pinM, INPUT);
}

int* getTrackingArray() {
    isObsL = digitalRead(pinL);
    if (isObsL == LOW) {
        res3[0] = 0;
    } else {
        res3[0] = 1;
    }

    isObsR = digitalRead(pinR);
    if (isObsR == LOW) {
        res3[1] = 0;
    } else {
        res3[1] = 1;
    }

    isObsM = digitalRead(pinM);
    if (isObsM == LOW) {
        res3[2] = 0;
    } else
    {
        res3[2] = 1;
    }

    // Serial.print(isObsL); Serial.print(" "); Serial.print(isObsR); Serial.print(" "); Serial.print(isObsM);
    // Serial.println(" ");

    return res3;
}