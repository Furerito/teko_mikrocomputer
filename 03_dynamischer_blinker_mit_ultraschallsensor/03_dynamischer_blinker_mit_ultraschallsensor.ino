const int buttonPin = 2;      // Trig-Pin des HC-SR04
const int ledPin = 5;       // LED an Pin 5 (PWM-Pin)


void setup() {
    Serial.begin(9600);      
    pinMode(ledPin, OUTPUT);
}

void loop() {
    int state = digitalRead(buttonPin);
    Serial.println(state);
    if (state == HIGH) {
    digitalWrite(ledPin, HIGH);
    } else {
    digitalWrite(ledPin, LOW);
    }

}
