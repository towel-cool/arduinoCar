#include <AFMotor.h>

// LEFT SIDE DRIVE
// RED BLACK BLANK RED BLACK

AF_DCMotor motor1(1);
// red black go forward
AF_DCMotor motor2(2);


void setup(){
  Serial.begin(9600);

}

void loop(){
  motor2.setSpeed(speed(200));
  motor2.run(FORWARD);
  delay(2000);
  motor2.run(RELEASE);
  delay(2000);
}

int  speed(int percent)
{
  return map(percent, 0, 200, 0, 255);
}