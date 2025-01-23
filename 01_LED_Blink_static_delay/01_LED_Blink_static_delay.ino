const int ledPin = 5;

// Die Setup-Funktion wird einmal beim Starten des Programms ausgeführt
void setup() {
    Serial.begin(9600);
    while(!Serial){}
    Serial.println("Here we go...");

    pinMode(ledPin, OUTPUT);
}

// Die Loop-Funktion wird wiederholt ausgeführt, solange das Programm läuft
// Wobei bei dieser Methode die grösste Zeit beim Serial.println() verloren geht
// Besser wäre wahrscheinlich zu beginn des loops eine led einschalten, am Ende Ausschalten und mit einem Oszilloskop zu messen

void loop() {
    unsigned long startTime = micros();
    // Code in der loop()-Funktion
    unsigned long duration = micros() - startTime;
    Serial.println(duration); // Gibt die Zeit in Mikrosekunden aus
}