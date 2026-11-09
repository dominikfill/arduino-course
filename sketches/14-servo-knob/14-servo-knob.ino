#include <Servo.h>

const int SERVO_PIN = 10;
const int POT_PIN = A0;
Servo motor;

void setup() {
  motor.attach(SERVO_PIN);
  Serial.begin(9600);
}

void loop() {
  int pot = analogRead(POT_PIN);
  int speed = map(pot, 0, 1023, 0, 180);
  Serial.print("Pot: ");
  Serial.print(pot);
  Serial.print(" - Speed: ");
  Serial.println(speed);
  motor.write(speed);
  delay(100);
}
