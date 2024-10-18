#include <Arduino.h>
#include <ezButton.h>

ezButton leftSwitch(48);
ezButton rightSwitch(42);

const int trig_Pin_FL = 44;
const int echo_Pin_FL = 38;

const int trig_Pin_FR = 32;
const int echo_Pin_FR = 34;

int threshold = 20;

int durationfl, durationfr, distfl, distfr;

int leftSwitchState, rightSwitchState;

int res2[4] = {9999,9999,9999,9999};

void setupObjectSensors() {
    pinMode(trig_Pin_FL, OUTPUT);
    pinMode(echo_Pin_FL, INPUT);

    pinMode(trig_Pin_FR, OUTPUT);
    pinMode(echo_Pin_FR, INPUT);

    rightSwitch.setDebounceTime(50);
    leftSwitch.setDebounceTime(50);
}

int* checkSurroundings() {
    digitalWrite(trig_Pin_FL, LOW);
    delayMicroseconds(2);
    digitalWrite(trig_Pin_FL, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_Pin_FL, LOW);
    durationfl = pulseIn(echo_Pin_FL, HIGH, 30000);
    distfl = durationfl > 0 ? (durationfl * 0.0343) / 2 : 9999;   

    digitalWrite(trig_Pin_FR, LOW);
    delayMicroseconds(2);
    digitalWrite(trig_Pin_FR, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_Pin_FR, LOW);
    durationfr = pulseIn(echo_Pin_FR, HIGH, 30000);
    distfr = durationfr > 0 ? (durationfr * 0.0343) / 2 : 9999;

    if (distfl <= threshold) {
      res2[0] = 0;
    } else {
      res2[0] = 1;
    }

    if (distfr <= threshold) {
      res2[1] = 0;
    } else {
      res2[1] = 1;
    }

    rightSwitch.loop();
    leftSwitch.loop();

    int leftSwitchState = leftSwitch.getState();
    int rightSwitchState = rightSwitch.getState();

    res2[2] = leftSwitchState;
    res2[3] = rightSwitchState;

    return res2;
}