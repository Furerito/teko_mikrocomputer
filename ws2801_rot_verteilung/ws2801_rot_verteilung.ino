#include <SPI.h>
#define DATA_PIN 11   // Data Leitung (DI)
#define CLOCK_PIN 13  // Clock Leitung (CI)
#define NUM_LEDS 25   // Anzahl der LEDs im Strip




void sendColor(byte red, byte green, byte blue) {
    SPI.transfer(red);   // R senden
    SPI.transfer(green); // G senden
    SPI.transfer(blue);  // B senden
}

void showLEDs() {
    delay(1); // Reset-Puls für WS2801
}

void setup() {
    SPI.begin();
    //SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
    pinMode(DATA_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    sendColor(0, 0, 0);
    showLEDs();
}

void loop() {

    for (int i = 0; i < NUM_LEDS; i++) {
        
        sendColor((i*10), (i*10), (i*10));
        
    }
    
    showLEDs();
      
}
