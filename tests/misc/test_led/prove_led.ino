const unsigned int RED_LED_PIN = 10;
const unsigned int YELLOW_LED_PIN = 11;
const unsigned int GREEN_LED_PIN = 12;
const unsigned int PAUSE = 500;

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(GREEN_LED_PIN, HIGH);
  delay(PAUSE);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, HIGH);
  delay(PAUSE);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, HIGH);
  delay(PAUSE);
  digitalWrite(RED_LED_PIN, LOW);
}

  

