#include <SPI.h>
#define DATA_PIN 11   // Data Leitung (DI)
#define CLOCK_PIN 13  // Clock Leitung (CI)
#define NUM_LEDS 25   // Anzahl der LEDs im Strip

byte ledBuffer[NUM_LEDS * 3]; // Buffer für alle LEDs (R, G, B)


// Setzt eine LED im Buffer auf die gewünschte Farbe
void setLED(int index, byte red, byte green, byte blue) {
    if (index < 0 || index >= NUM_LEDS) return; // Sicherstellen, dass die LED existiert
    int pos = index * 3;
    ledBuffer[pos] = red;
    ledBuffer[pos + 1] = green;
    ledBuffer[pos + 2] = blue;
}

// Sendet den gesamten Buffer per SPI an den WS2801
void showLEDs() {
    SPI.transfer(ledBuffer,(NUM_LEDS * 3));
    delay(1); // Reset-Puls für WS2801
}


void setup() {
    SPI.begin();
    pinMode(DATA_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
}

void loop() {
    for (int j = 0; j < NUM_LEDS; j++) {
      for (int i = 0; i < NUM_LEDS; i++) {
        if(j == i){
          setLED(i, 200, 200, 200);
        }
      }
      showLEDs();
      delay(100);
    }
    
    
    
}
