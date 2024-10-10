#include <Arduino.h>
#include <ezButton.h>

ezButton btnLeft(41);
ezButton btnRight(39);

// Front Left Sensors
// const int ir_pin_fl = 53;
// int is_obs_fl_ir = HIGH;
const int trig_Pin_FL = 38;
const int echo_Pin_FL = 40;

// Front Right Sensors
// const int ir_pin_fr = 36;
// // int is_obs_fr_ir = HIGH;
// const int trig_Pin_FR = 46;
// const int echo_Pin_FR = 48;

// // Back Left Sensors
// // const int ir_pin_bl = 43;
// // int is_obs_bl_ir = HIGH;
// const int trig_Pin_BL = 42;
// const int echo_Pin_BL = 44;

// // Back Right Sensors
// // const int ir_pin_br = 32;
// // int is_obs_br_ir = HIGH;
// const int trig_Pin_BR = 37;
// const int echo_Pin_BR = 33;

int durationbl, durationbr, durationfl, durationfr;

int res2[4] = {9999,9999,9999};

void setupObjectSensors() {
    // pinMode(ir_pin_fl, INPUT);
    // pinMode(ir_pin_fr, INPUT);
    // pinMode(ir_pin_bl, INPUT);
    // pinMode(ir_pin_br, INPUT);

    pinMode(trig_Pin_FL, OUTPUT);
    pinMode(echo_Pin_FL, INPUT);

    // pinMode(trig_Pin_FR, OUTPUT);
    // pinMode(echo_Pin_FR, INPUT);

    // pinMode(trig_Pin_BL, OUTPUT);
    // pinMode(echo_Pin_BL, INPUT);

    // pinMode(trig_Pin_BR, OUTPUT);
    // pinMode(echo_Pin_BR, INPUT);
}

int* checkSurroundings() {
  // Front Left Sensor
    digitalWrite(trig_Pin_FL, LOW);
    digitalWrite(trig_Pin_FL, HIGH);
    digitalWrite(trig_Pin_FL, LOW);
    durationfl = pulseIn(echo_Pin_FL, HIGH, 30000);
    res2[0] = durationfl > 0 ? (durationfl * 0.0343) / 2 : 9999;

    res2[1] = btnLeft.getState();
    res2[2] = btnLeft.getState();   


    return res2;
}