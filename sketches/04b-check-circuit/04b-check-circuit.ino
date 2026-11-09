const int LED_PIN = 9;
const int POT_PIN = A0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  Serial.println(analogRead(POT_PIN));
  delay(250);
  digitalWrite(LED_PIN, LOW);
  delay(250);
}