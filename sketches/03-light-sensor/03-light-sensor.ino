// Read a light sensor (LDR in a voltage divider) on A0
// and print the value to the Serial Monitor.

const int sensorPin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int light = analogRead(sensorPin);  // 0 (dark) to 1023 (bright)
  Serial.println(light);
  delay(100);
}
