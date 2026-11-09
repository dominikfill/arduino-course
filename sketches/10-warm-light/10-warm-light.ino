const int LED_PIN = 9;
const int TEMP_PIN = A1;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int reading = analogRead(TEMP_PIN);
  float volts = reading * (5.0 / 1023.0);
  float celsius = (volts - 0.5) * 100.0;
  Serial.println(celsius);
  if (celsius > 27.0) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  delay(500);
}
