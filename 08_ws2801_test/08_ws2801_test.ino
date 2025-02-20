#include <FastLED.h>

#define NUM_LEDS 25  // Anzahl der LEDs im Strip
#define DATA_PIN 11  // Data Pin
#define CLOCK_PIN 13 // Clock Pin

CRGB leds[NUM_LEDS];

void setup() {
    FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
    static uint8_t hue = 0; // Startfarbe

    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(hue + (i * 10), 250, 250); // Jede LED leicht verschoben färben
    }

    FastLED.show();
    hue++; // Farbe langsam verschieben
    //delay(3); // Geschwindigkeit der Welle
}
