#include <IRremote.h>

#define IR_PIN 2  // Der Pin für den IR-Empfänger

IRrecv irrecv(IR_PIN);

void setup() {
    Serial.begin(9600);
    while (!Serial)
        ; // Wait for Serial to become available. Is optimized away for some cores.
    irrecv.begin(IR_PIN, ENABLE_LED_FEEDBACK);  // Startet den IR-Empfang
}

void loop() {
    if (irrecv.decode()) {
        Serial.print("Empfangen: ");
        Serial.println(irrecv.decodedIRData.decodedRawData, HEX);  // Gibt den Code in HEX aus
        irrecv.resume();  // Empfänger für das nächste Signal vorbereiten
    }
}
