#define DATA_PIN 11   // Data Leitung (DI)
#define CLOCK_PIN 13  // Clock Leitung (CI)
#define NUM_LEDS 25   // Anzahl der LEDs im Strip

//int analogPin = A0; //Regler für rot 

void setup() {
    pinMode(DATA_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
}

void sendColor(byte red, byte green, byte blue) {
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, red);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, green);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, blue);
}

void showLEDs() {
    digitalWrite(DATA_PIN, LOW);
    delayMicroseconds(500); // Reset-Impuls für WS2801
}

void loop() {
    for (int i = 0; i < NUM_LEDS; i++) {
        // LEDs ausschalten
        for (int j = 0; j < NUM_LEDS; j++) {
            if (j == i) {
                sendColor(255, 255, 255); // Weiss
            } else {
                sendColor(0, 0, 0); // Aus
            }
        }
        showLEDs();
        delay(40); // Geschwindigkeit der Bewegung anpassen
    }
}
