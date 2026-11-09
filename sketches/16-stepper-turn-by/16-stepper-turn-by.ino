#include <Stepper.h>

const int STEPS_PER_TURN = 2048;
Stepper motor(STEPS_PER_TURN, 8, 10, 9, 11);

void setup() {
  motor.setSpeed(10);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    int angle = Serial.readStringUntil('\n').toInt();
    int steps = map(angle, 0, 360, 0, STEPS_PER_TURN);
    motor.step(steps);
    Serial.print("Turned by ");
    Serial.print(angle);
    Serial.println(" degrees");
  }
}
