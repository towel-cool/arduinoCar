#include <Arduino.h>
#include <ezButton.h>

ezButton leftSwitch(48);
ezButton rightSwitch(42);
ezButton middleSwitch(33);

const int trig_Pin_FL = 44;
const int echo_Pin_FL = 38;

const int trig_Pin_FR = 32;
const int echo_Pin_FR = 34;

const int trig_Pin_M = 36;
const int echo_Pin_M = 46;

int threshold = 15;

int durationfl, durationfr, durationm, distfl, distfr, distm;

int leftSwitchState, rightSwitchState;

int res2[6] = {9999,9999,9999,9999,9999,9999};

void setupObjectSensors() {
    pinMode(trig_Pin_FL, OUTPUT);
    pinMode(echo_Pin_FL, INPUT);

    pinMode(trig_Pin_FR, OUTPUT);
    pinMode(echo_Pin_FR, INPUT);

    pinMode(trig_Pin_M, OUTPUT);
    pinMode(echo_Pin_M, INPUT);

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

    digitalWrite(trig_Pin_M, LOW);
    delayMicroseconds(2);
    digitalWrite(trig_Pin_M, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_Pin_M, LOW);
    durationm = pulseIn(echo_Pin_M, HIGH, 30000);
    distm = durationm > 0 ? (durationm * 0.0343) / 2 : 9999;

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

    if (distm <= threshold) {
      res2[2] = 0;
    } else {
      res2[2] = 1;
    }

    //print ultrasonic distances
    // Serial.print(distfl);
    // Serial.print(" ");
    // Serial.print(distfr);
    // Serial.print(" ");
    // Serial.print(distfr);
    // Serial.print(" ");
    // Serial.print(distm);
    // Serial.println(" ");

    rightSwitch.loop();
    leftSwitch.loop();
    middleSwitch.loop();

    int leftSwitchState = leftSwitch.getState();
    int rightSwitchState = rightSwitch.getState();
    int middleSwitchState = middleSwitch.getState();

    res2[3] = leftSwitchState;
    res2[4] = rightSwitchState;
    res2[5] = middleSwitchState;

    return res2;
}