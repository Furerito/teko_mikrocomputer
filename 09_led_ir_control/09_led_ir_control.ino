#include <SPI.h>
#include <IRremote.h>

#define DATA_PIN 11  
#define CLOCK_PIN 13  
#define NUM_LEDS 25  
#define IR_PIN 2  // IR-Empfänger an Pin D2

IRrecv irrecv(IR_PIN);

// IR-Codes (ersetze diese mit deinen eigenen Werten!)
#define IR_UP    0xB946FF00
#define IR_DOWN  0xEA15FF00
#define IR_LEFT  0xBB44FF00
#define IR_RIGHT 0xBC43FF00

byte ledBuffer[NUM_LEDS * 3];

int posX = 2, posY = 2;  // Startposition: Mitte (2,2)

// Wandelt (x, y)-Koordinaten in den LED-Index um (Serpentinenverlauf)
int getLEDIndex(int x, int y) {
    int originalIndex;
    if (y % 2 == 0) {
        originalIndex = y * 5 + x;
    } else {
        originalIndex = y * 5 + (4 - x);
    }
    return NUM_LEDS - 1 - originalIndex;  // Hier wird das Feld umgedreht
}

// Setzt eine LED im Buffer auf die gewünschte Farbe
void setLED(int index, byte red, byte green, byte blue) {
    if (index < 0 || index >= NUM_LEDS) return;
    int pos = index * 3;
    ledBuffer[pos] = red;
    ledBuffer[pos + 1] = green;
    ledBuffer[pos + 2] = blue;
}

// Sendet den gesamten Buffer per SPI an den WS2801
void showLEDs() {
    digitalWrite(CLOCK_PIN, LOW);
    for (int i = 0; i < NUM_LEDS * 3; i++) {
        SPI.transfer(ledBuffer[i]);
    }
    delay(1);
}

// Setzt alle LEDs auf Schwarz
void clearLEDs() {
    memset(ledBuffer, 0, sizeof(ledBuffer));
}

// Aktualisiert die LED-Position
void updateLED() {
    clearLEDs();
    setLED(getLEDIndex(posX, posY), 200, 200, 200);
    showLEDs();
}

void setup() {
    

    Serial.begin(9600);
    while (!Serial)
        ; // Wait for Serial to become available. Is optimized away for some cores.
        SPI.begin();

    pinMode(DATA_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);

    irrecv.begin(IR_PIN, ENABLE_LED_FEEDBACK);  // Startet den IR-Empfang

    updateLED();  // Startposition setzen
}

void loop() {
  /*
  if (irrecv.decode()) {
        Serial.print("Empfangen: ");
        Serial.println(irrecv.decodedIRData.decodedRawData, HEX);  // Gibt den Code in HEX aus
        irrecv.resume();  // Empfänger für das nächste Signal vorbereiten
    }
    */
    if (irrecv.decode()) {
        unsigned long command = irrecv.decodedIRData.decodedRawData;
        Serial.println(command);
        // Bewegung basierend auf der Fernbedienung
        if (command == IR_UP && posY > 0) posY--;
        if (command == IR_DOWN && posY < 4) posY++;
        if (command == IR_LEFT && posX > 0) posX--;
        if (command == IR_RIGHT && posX < 4) posX++;

        updateLED();  // Position aktualisieren
        irrecv.resume();  // IR für nächstes Signal vorbereiten
    }
}
