const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  Serial.begin(9600);
}

void colour(String name, int red, int green, int blue) {
  Serial.println(name);
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
  delay(2000);
}

void loop() {
  colour("yellow", 255, 40, 0);
  colour("orange", 255, 15, 0);
  colour("purple", 255, 0, 40);
  colour("white",  255, 70, 60);
}
