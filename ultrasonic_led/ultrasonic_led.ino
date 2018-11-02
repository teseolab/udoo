int SensorReadingcm;
#define UltrasonicTriggerPin 5
#define UltrasonicEchoPin 2
#define ledPin 9
#define limit 20

void setup() {
  // Init serial communication

  Serial.begin(115200);

  pinMode(UltrasonicTriggerPin, OUTPUT);
  pinMode(UltrasonicEchoPin, INPUT);

  pinMode(ledPin, OUTPUT);
  
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
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  Serial.println(SensorReadingcm);
  delay(1000);

}


long microsecondsToCentimeters(long ms){
  return ms / 29.154 / 2;
  
}


