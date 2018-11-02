int SensorReadingcm;
#define UltrasonicTrigerPin 5
#define UltrasonicEchoPin 2


void setup() {
  // Init serial communication

  Serial.begin(115200);

  pinMode(UltrasonicTrigerPin, OUTPUT);
  pinMode(UltrasonicEchoPin, INPUT);
  

}

void loop() {
  float duration;

  digitalWrite(UltrasonicTrigerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(UltrasonicTrigerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(UltrasonicTrigerPin, LOW);

  duration = pulseIn(UltrasonicEchoPin, HIGH);

  SensorReadingcm = microsecondsToCentimeters(duration);

  Serial.println(SensorReadingcm);
  delay(1000);

}


long microsecondsToCentimeters(long ms){
  return ms / 29.154 / 2;
  
}


