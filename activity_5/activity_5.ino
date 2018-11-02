const int ledPin = 9;


void setup() {
  // Init serial communication

  pinMode(ledPin, OUTPUT);

}

void loop() {

  digitalWrite(ledPin, HIGH);
  delay(3000);

  digitalWrite(ledPin, LOW);
  delay(3000);
}
