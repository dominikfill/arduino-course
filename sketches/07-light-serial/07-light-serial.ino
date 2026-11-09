const int LIGHT_PIN = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int light = analogRead(LIGHT_PIN);
  Serial.println(light);
  delay(100);
}
