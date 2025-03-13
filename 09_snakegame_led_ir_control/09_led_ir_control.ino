#include <SPI.h>
#include <IRremote.h>

#define DATA_PIN 11
#define CLOCK_PIN 13
#define NUM_LEDS 25
#define IR_PIN 2
#define RESET_PIN 3

IRrecv irrecv(IR_PIN);

// IR-Codes (an deine Fernbedienung anpassen!)
#define IR_UP    0xB946FF00
#define IR_DOWN  0xEA15FF00
#define IR_LEFT  0xBB44FF00
#define IR_RIGHT 0xBC43FF00

byte ledBuffer[NUM_LEDS * 3];
byte foodPosition[2];

// Snake-Variablen
int snakeX[25] = {2};  // Maximale Länge = 25 (ganzes Feld)
int snakeY[25] = {2};
int snakeLength = 1;
enum Direction { UP, DOWN, LEFT, RIGHT, NONE };
Direction currentDir = NONE;
unsigned long lastMove = 0;

int getLEDIndex(int x, int y) {
    int originalIndex;
    if(y % 2 == 0) {
        originalIndex = y * 5 + x;
    } else {
        originalIndex = y * 5 + (4 - x);
    }
    return NUM_LEDS - 1 - originalIndex;
}

void setLED(int index, byte r, byte g, byte b) {
    if(index < 0 || index >= NUM_LEDS) return;
    int pos = index * 3;
    ledBuffer[pos] = r;
    ledBuffer[pos + 1] = g;
    ledBuffer[pos + 2] = b;
}

void showLEDs() {
    digitalWrite(CLOCK_PIN, LOW);
    SPI.transfer(ledBuffer, NUM_LEDS * 3);
}

void clearLEDs() {
    memset(ledBuffer, 0, sizeof(ledBuffer));
}

void generateNewFood() {
    bool valid;
    do {
        valid = true;
        foodPosition[0] = random(0, 5);
        foodPosition[1] = random(0, 5);
        
        // Prüfe ob Position von Schlange belegt
        for(int i=0; i<snakeLength; i++) {
            if(foodPosition[0] == snakeX[i] && foodPosition[1] == snakeY[i]) {
                valid = false;
                break;
            }
        }
    } while(!valid);
}

bool checkCollision(int x, int y) {
    // Selbstkollision prüfen (ab Index 1)
    for(int i=1; i<snakeLength; i++) {
        if(x == snakeX[i] && y == snakeY[i]) return true;
    }
    return false;
}

void gameOver() {
    // Blink-Effekt
    for(int i=0; i<3; i++) {
        clearLEDs();
        showLEDs();
        delay(500);
        for(int j=0; j<snakeLength; j++) {
            setLED(getLEDIndex(snakeX[j], snakeY[j]), 255, 0, 0);
        }
        showLEDs();
        delay(500);
    }
    
    // Reset
    snakeLength = 1;
    snakeX[0] = 2;
    snakeY[0] = 2;
    currentDir = NONE;
    generateNewFood();
    updateLED();
}

void updateLED() {
    clearLEDs();
    
    // Schlange zeichnen
    for(int i=0; i<snakeLength; i++) {
        byte r = (i == 0) ? 0 : 255;  // Kopf weiß
        byte g = 255;                  // Körper grün
        byte b = (i == 0) ? 0 : 255;
        setLED(getLEDIndex(snakeX[i], snakeY[i]), r, g, b);
    }
    
    // Futter zeichnen
    setLED(getLEDIndex(foodPosition[0], foodPosition[1]), 255, 0, 0);
    
    showLEDs();
}

void setup() {
    //Serial.begin(9600);
    
    SPI.begin();
    pinMode(DATA_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(RESET_PIN, INPUT_PULLUP);
    irrecv.begin(IR_PIN, ENABLE_LED_FEEDBACK);
    randomSeed(analogRead(A0));
    generateNewFood();
    updateLED();
}

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void loop() {

    //Prüfe Reset Button
    if(digitalRead(RESET_PIN) == HIGH){
      delay(300);
      resetFunc();
      delay(1000);
    }

    // IR-Empfang
    if(irrecv.decode()) {
        unsigned long command = irrecv.decodedIRData.decodedRawData;
        
        if(command == IR_RIGHT && currentDir != LEFT) currentDir = RIGHT;
        if(command == IR_LEFT && currentDir != RIGHT) currentDir = LEFT;
        if(command == IR_UP && currentDir != DOWN) currentDir = UP;
        if(command == IR_DOWN && currentDir != UP) currentDir = DOWN;
        
        irrecv.resume();
    }

    // Spiel-Logik
    if(millis() - lastMove > 300 && currentDir != NONE) {
        lastMove = millis();
        
        // Neue Kopfposition berechnen
        int newHeadX = snakeX[0];
        int newHeadY = snakeY[0];
        
        switch(currentDir) {
            case RIGHT: newHeadX = (newHeadX + 1) % 5; break;
            case LEFT:  newHeadX = (newHeadX - 1 + 5) % 5; break;
            case UP:    newHeadY = (newHeadY - 1 + 5) % 5; break;
            case DOWN:  newHeadY = (newHeadY + 1) % 5; break;
        }
        
        // Kollision
        if(checkCollision(newHeadX, newHeadY)) {
            gameOver();
            return;
        }
        
        // Körper bewegen
        for(int i = snakeLength; i > 0; i--) {
            snakeX[i] = snakeX[i-1];
            snakeY[i] = snakeY[i-1];
        }
        
        // Kopf aktualisieren
        snakeX[0] = newHeadX;
        snakeY[0] = newHeadY;
        
        // Futter gefressen?
        if(newHeadX == foodPosition[0] && newHeadY == foodPosition[1]) {
            snakeLength = min(snakeLength + 1, 25);
            generateNewFood();
        }
        
        updateLED();
    }
}