const int analogPin = A0;       // Analoger Pin, an dem der Spannungsteiler angeschlossen ist
const float V_in = 5.0;         // Versorgungsspannung (5V bei Arduino Uno)
const float R_ref = 100;        // Referenzwiderstand in Ohm

void setup() {
    Serial.begin(9600);
    pinMode(analogPin, OUTPUT);
}

void loop() {
    int analogValue = analogRead(analogPin); // Analogwert lesen (0–1023)

    // Widerstand berechnen
    float R_measured = R_ref * ((float)analogValue / (1023 - analogValue));

    // Ergebnis ausgeben
    Serial.print("Analog Value: ");
    Serial.print(analogValue);
    Serial.print(" -> Measured Resistance: ");
    Serial.print(R_measured);
    Serial.println(" Ohms");

    delay(500); // Kleine Pause für Lesbarkeit
}
