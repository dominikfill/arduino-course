#include <Servo.h>

const int SERVO_PIN = 10;
Servo motor;

void setup() {
  motor.attach(SERVO_PIN);
}

void loop() {
  motor.write(0);
  delay(2000);
  motor.write(90);
  delay(1000);
  motor.write(180);
  delay(2000);
  motor.write(90);
  delay(1000);
}
