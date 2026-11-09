const int LED_PIN = 9;
const int POT_PIN = A0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int brightness = analogRead(POT_PIN) / 4;
  analogWrite(LED_PIN, brightness);
}
