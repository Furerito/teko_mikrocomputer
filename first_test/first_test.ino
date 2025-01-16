// Die Setup-Funktion wird einmal beim Starten des Programms ausgeführt
void setup() {
    Serial.begin(9600);
    while(!Serial){}
    Serial.println("Here we go...");
}

// Die Loop-Funktion wird wiederholt ausgeführt, solange das Programm läuft
void loop() {
  Serial.println("we are loooping...");
  delay(2000);
}