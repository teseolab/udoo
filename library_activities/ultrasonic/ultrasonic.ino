// Sound
const int soundPin = 8;
int toneLength = 500;

// HC-SR04
const int trigPin = 9;
const int echoPin = 11;


float duration, distance, hz;
int analogIn;

void setup() {
    tone(soundPin, 440, 2*toneLength); // Plays a tone to confirm setup
    delay(toneLength);

    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    Serial.begin(9600); // Starts the serial communication
}

void loop() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    duration = pulseIn(echoPin, HIGH);
    distance = microsecondsToCentimeters(duration);

    Serial.println("Distance");
    Serial.println(distance);
    
    // tone(soundPin, hz, toneLength);

    Serial.println("Photo resistor");
    analogIn = analogRead(0);
    Serial.println(analogIn);

    // should go below 50 if a finger touches the sensor
    if (analogIn < 50) {
        tone(soundPin, hz, toneLength);
        Serial.println("Hz");
        hz = cmToHz(distance);
        Serial.println(hz);
    }
    
    delay(toneLength*2);
}

float microsecondsToCentimeters(float ms){
    return ms / 29.154 / 2;
}

// Notes and their freqs: http://pages.mtu.edu/~suits/notefreqs.html
float cmToHz(float cm){
    // map(value, fromLow, fromHigh, toLow, toHigh)
    cm = constrain(cm, 1, 100);
    return map(cm, 1, 100, 220, 880); // map returns a long value
}
