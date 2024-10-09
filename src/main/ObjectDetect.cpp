#include <Arduino.h>

// Front Left Sensors
const int ir_pin_fl = 53;
int is_obs_fl_ir = HIGH;
const int trig_Pin_FL = 38;
const int echo_Pin_FL = 40;

// Front Right Sensors
const int ir_pin_fr = 36;
int is_obs_fr_ir = HIGH;
const int trig_Pin_FR = 46;
const int echo_Pin_FR = 48;

// Back Left Sensors
const int ir_pin_bl = 43;
int is_obs_bl_ir = HIGH;
const int trig_Pin_BL = 42;
const int echo_Pin_BL = 44;

// Back Right Sensors
const int ir_pin_br = 32;
int is_obs_br_ir = HIGH;
const int trig_Pin_BR = 37;
const int echo_Pin_BR = 33;

int durationbl, durationbr, durationfl, durationfr;

int res2[8] = {0,0,0,0,0,0,0,0};

void setupObjectSensors() {
    pinMode(ir_pin_fl, INPUT);
    pinMode(ir_pin_fr, INPUT);
    pinMode(ir_pin_bl, INPUT);
    pinMode(ir_pin_br, INPUT);

    pinMode(trig_Pin_FL, OUTPUT);
    pinMode(echo_Pin_FL, INPUT);

    pinMode(trig_Pin_FR, OUTPUT);
    pinMode(echo_Pin_FR, INPUT);

    pinMode(trig_Pin_BL, OUTPUT);
    pinMode(echo_Pin_BL, INPUT);

    pinMode(trig_Pin_BR, OUTPUT);
    pinMode(echo_Pin_BR, INPUT);
}

int checkSurroundings() {
    is_obs_fl_ir = digitalRead(ir_pin_fl);
    if (is_obs_fl_ir == LOW)
    {
        res2[0] = 0;
    }
    else
    {
        res2[0] = 1;
    }
    is_obs_fr_ir = digitalRead(ir_pin_fr);
    if (is_obs_fr_ir == LOW)
    {
        res2[1] = 0;
    }
    else
    {
        res2[1] = 1;
    }
    is_obs_bl_ir = digitalRead(ir_pin_bl);
    if (is_obs_bl_ir == LOW)
    {
        res2[2] = 0;
    }
    else
    {
        res2[2] = 1;
    }
    is_obs_br_ir = digitalRead(ir_pin_br);
    if (is_obs_br_ir == LOW)
    {
        res2[3] = 0;
    }
    else
    {
        res2[3] = 1;
    }

  digitalWrite(trig_Pin_FL, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_Pin_FL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_Pin_FL, LOW);

    durationfl = pulseIn(echo_Pin_FL, HIGH);
    durationfr = pulseIn(echo_Pin_FR, HIGH);
    durationbl = pulseIn(echo_Pin_BL, HIGH);
    durationbr = pulseIn(echo_Pin_BR, HIGH);

    Serial.println((durationfl*.0343)/2);

    res2[4] = (durationfl*.0343)/2;
    res2[5] = (durationfr*.0343)/2;
    res2[6] = (durationbl*.0343)/2;
    res2[7] = (durationbr*.0343)/2;

    // for (int i = 0; i < 8; i++) {
    //   Serial.print(res2[i]);
    // }
    // Serial.println(" ");

    return res2;
}