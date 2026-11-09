const int POT_PIN = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int knob = analogRead(POT_PIN);
  Serial.println(knob);
  delay(100);
}
