const int LED_PIN = 9;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  analogWrite(LED_PIN, 255);
  delay(1000);
  analogWrite(LED_PIN, 60);
  delay(1000);
  analogWrite(LED_PIN, 10);
  delay(1000);
}
