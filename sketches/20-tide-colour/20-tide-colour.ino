// The water level in Venice as a colour: low = blue, high = red
#include "tide_data.h"

const int RED_PIN = 9;
const int BLUE_PIN = 11;
int hour = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int cm = constrain(tide[hour], 0, 140);

  analogWrite(RED_PIN, map(cm, 0, 140, 0, 255));
  analogWrite(BLUE_PIN, map(cm, 0, 140, 60, 0));

  Serial.println(String(hour) + ":00  " + tide[hour] + " cm");

  hour = (hour + 1) % HOURS; // Loops back to 0 automatically
  delay(1000);
}