#include <Stepper.h>

const int STEPS_PER_TURN = 2048;
Stepper motor(STEPS_PER_TURN, 8, 10, 9, 11);

void setup() {
  motor.setSpeed(10);
}

void loop() {
  motor.step(512);
  delay(1000);
  motor.step(-512);
  delay(1000);
}
