int SensorReadingcm;
#define UltrasonicTriggerPin 5
#define UltrasonicEchoPin 2
#define ledGreenPin 9
#define ledRedPin 9
#define limit 20

void setup() {
  // Init serial communication

  Serial.begin(115200);

  pinMode(UltrasonicTriggerPin, OUTPUT);
  pinMode(UltrasonicEchoPin, INPUT);

  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledRedPin, OUTPUT);
  
}

void loop() {
  float duration;



  digitalWrite(UltrasonicTriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(UltrasonicTriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(UltrasonicTriggerPin, LOW);

  duration = pulseIn(UltrasonicEchoPin, HIGH);

  SensorReadingcm = microsecondsToCentimeters(duration);

  if (SensorReadingcm < limit ) {
    digitalWrite(ledRedPin, HIGH);
    digitalWrite(ledGreenPin, LOW);
  } else {
    digitalWrite(ledRedPin, LOW);
    digitalWrite(ledGreenPin, HIGH);
  }
  Serial.println(SensorReadingcm);
  delay(1000);

}


long microsecondsToCentimeters(long ms){
  return ms / 29.154 / 2;
  
}


