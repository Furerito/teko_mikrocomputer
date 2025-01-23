const int ledPin = 5;

// Die Setup-Funktion wird einmal beim Starten des Programms ausgeführt
void setup() {
    Serial.begin(9600);
    while(!Serial){}
    Serial.println("Here we go...");

    pinMode(ledPin, OUTPUT);
}

// Die Loop-Funktion wird wiederholt ausgeführt, solange das Programm läuft
void loop() {
  Serial.println("we are loooping...");
  digitalWrite(ledPin,HIGH);
  
  delay(1000);
  digitalWrite(ledPin,LOW);
  delay(1000);
}