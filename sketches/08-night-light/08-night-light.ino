const int LED_PIN = 9;
const int LIGHT_PIN = A0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int light = analogRead(LIGHT_PIN);
  Serial.println(light);

  int brightness = map(light, 100, 900, 255, 0);
  brightness = constrain(brightness, 0, 255);
  analogWrite(LED_PIN, brightness);

  delay(50);
}
