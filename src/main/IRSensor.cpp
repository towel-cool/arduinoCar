#include <Arduino.h>

int pinFL = 52;
int isObsFL = HIGH;                                                                       
int pinFR = 26;
int isObsFR = HIGH;
int pinBL = 50;
int isObsBL = HIGH;
int pinBR = 28;
int isObsBR = HIGH;

int res1[4] = {0,0,0,0};

void setupIR() {
    pinMode(pinFL, INPUT);
    pinMode(pinFR, INPUT);
    pinMode(pinBL, INPUT);
    pinMode(pinBR, INPUT);
}

int* checkGround() {
    isObsFL = digitalRead(pinFL);
    if (isObsFL == LOW)
    {
        res1[0] = 0;
    }
    else
    {
        res1[0] = 1;
    }
    isObsFR = digitalRead(pinFR);
    if (isObsFR == LOW)
    {
        res1[1] = 0;
    }
    else
    {
        res1[1] = 1;
    } 
    isObsBL = digitalRead(pinBL);
    if (isObsBL == LOW)
    {
        res1[2] = 0;
    }
    else
    {
        res1[2] = 1;
    }  
    isObsBR = digitalRead(pinBR);
    if (isObsBR == LOW)
    {
        res1[3] = 0;
    }
    else
    {
        res1[3] = 1;
    } 

    return res1;
}