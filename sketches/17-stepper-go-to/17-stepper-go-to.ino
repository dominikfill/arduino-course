#include <Stepper.h>

const int STEPS_PER_TURN = 2048;
Stepper motor(STEPS_PER_TURN, 8, 10, 9, 11);
int position = 0;

void setup() {
  motor.setSpeed(10);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    int angle = Serial.readStringUntil('\n').toInt();
    int target = map(angle, 0, 360, 0, STEPS_PER_TURN);
    motor.step(target - position);
    position = target;
    Serial.print("Now at ");
    Serial.print(angle);
    Serial.println(" degrees");
  }
}
