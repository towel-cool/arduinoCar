#include <Arduino.h>

int pinFL = 52;
int isObsFL = HIGH;                                                                       
int pinFR = 26;
int isObsFR = HIGH;
int pinFM = 53;
int isObsFM = HIGH;
int pinBL = 50;
int isObsBL = HIGH;
int pinBR = 28;
int isObsBR = HIGH;
int pinBM = 33;
int isObsBM = HIGH;

int res[6] = {0,0,0,0,0,0};

void setupIR() {
    pinMode(pinFL, INPUT);
    pinMode(pinFR, INPUT);
    pinMode(pinFM, INPUT);
    pinMode(pinBL, INPUT);
    pinMode(pinBR, INPUT);
    pinMode(pinBM, INPUT);
}

int* checkGround() {
    isObsFL = digitalRead(pinFL);
    if (isObsFL == LOW)
    {
        res[0] = 0;
    }
    else
    {
        res[0] = 1;
    }
    isObsFM = digitalRead(pinFM);
    if (isObsFM == LOW)
    {
        res[1] = 0;
    }
    else
    {
        res[1] = 1;
    }  
    isObsFR = digitalRead(pinFR);
    if (isObsFR == LOW)
    {
        res[2] = 0;
    }
    else
    {
        res[2] = 1;
    } 
    isObsBL = digitalRead(pinBL);
    if (isObsBL == LOW)
    {
        res[3] = 0;
    }
    else
    {
        res[3] = 1;
    }  
    isObsBM = digitalRead(pinBM);
    if (isObsBM == LOW)
    {
        res[4] = 0;
    }
    else
    {
        res[4] = 1;
    }
    isObsBR = digitalRead(pinBR);
    if (isObsBR == LOW)
    {
        res[5] = 0;
    }
    else
    {
        res[5] = 1;
    } 

    return res;
}