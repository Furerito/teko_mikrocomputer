const int trigPin = 9;      // Trig-Pin des HC-SR04
const int echoPin = 10;     // Echo-Pin des HC-SR04
const int ledPin = 5;       // LED an Pin 5 (PWM-Pin)

// Variablen für den Ultraschall
float duration, distance; 

void setup() {
    Serial.begin(9600);      
    pinMode(trigPin, OUTPUT);  
    pinMode(echoPin, INPUT);  
    pinMode(ledPin, OUTPUT);

}

void loop() {
    // Ultraschall-Signal senden
    digitalWrite(trigPin, LOW);  
    delayMicroseconds(2);  
    digitalWrite(trigPin, HIGH);  
    delayMicroseconds(10);  
    digitalWrite(trigPin, LOW);  
    duration = pulseIn(echoPin, HIGH);  
    distance = (duration*.0343)/2;  
    Serial.print("Distance: ");  
    Serial.println(distance);  
    
    // Entfernung auf eine Verzögerungszeit (10 bis 1000 ms) umrechnen
    int delayTime = map(distance, 3, 120, 10, 1000); // Bereich: 2 cm bis 40 cm
    delayTime = constrain(delayTime, 10, 1000);      // Begrenzen auf sinnvolle Werte
    digitalWrite(ledPin, HIGH);
    delay(delayTime);  
    digitalWrite(ledPin, LOW);
    delay(delayTime);  

}
