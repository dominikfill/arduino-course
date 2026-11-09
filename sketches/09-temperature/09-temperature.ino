const int TEMP_PIN = A1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int reading = analogRead(TEMP_PIN);
  float volts = reading * (5.0 / 1023.0);
  float celsius = (volts - 0.5) * 100.0;
  Serial.println(celsius);
  delay(500);
}
