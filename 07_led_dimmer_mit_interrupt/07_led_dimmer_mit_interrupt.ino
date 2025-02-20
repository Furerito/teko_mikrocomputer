#define debug_print                                               // manages most of the print and println debug, not all but most

#if defined debug_print
   #define debug_begin(x)        Serial.begin(x)
   #define debug(x)                   Serial.print(x)
   #define debugln(x)                 Serial.println(x)
#else
   #define debug_begin(x)
   #define debug(x)
   #define debugln(x)
#endif

const int ledPin = 3;
const int buttonPin = 2;

bool ledState = false;
int pwmValue = 0;
int dimDirection = 1;  // 1 für Aufwärtsdimmen, -1 für Abwärtsdimmen

unsigned long buttonPressStartTime = 0;
bool isButtonPressed = false;
bool longPressActive = false;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

unsigned long lastDimStepTime = 0;
const unsigned long dimStepInterval = 30;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(ledPin, LOW);
}

void loop() {
  int currentButtonState = digitalRead(buttonPin);
  unsigned long currentMillis = millis();
debugln(currentButtonState);
  // Entprellung des Buttons
  if (currentButtonState == LOW && (currentMillis - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = currentMillis;

    if (!isButtonPressed) {
      // Button wurde gerade gedrückt
      isButtonPressed = true;
      buttonPressStartTime = currentMillis;
      longPressActive = false;
    } else {
      // Button ist weiterhin gedrückt
      unsigned long pressDuration = currentMillis - buttonPressStartTime;

      // Langer Druck erkennen (ab 500ms)
      if (pressDuration >= 500 && !longPressActive) {
        longPressActive = true;
      }

      // Dimmen während langer Druck
      if (longPressActive && ledState) {
        if (currentMillis - lastDimStepTime >= dimStepInterval) {
          pwmValue += dimDirection;
          pwmValue = constrain(pwmValue, 0, 255);
          analogWrite(ledPin, pwmValue);
          lastDimStepTime = currentMillis;

          // Richtung umkehren wenn Limit erreicht
          if (pwmValue == 0 || pwmValue == 255) {
            dimDirection *= -1;
            longPressActive = false;
          }
        }
      }
    }
  } 
  else if (currentButtonState == HIGH && isButtonPressed) {
    // Button wurde losgelassen
    isButtonPressed = false;
    unsigned long pressDuration = currentMillis - buttonPressStartTime;

    if (longPressActive) {
      // Beende langes Drücken und kehre Richtung um
      dimDirection *= -1;
    } else if (pressDuration < 500) {
      // Kurzer Druck - LED-Zustand ändern
      ledState = !ledState;
      if (ledState) {
        analogWrite(ledPin, pwmValue);
      } else {
        analogWrite(ledPin, 0);
      }
    }
  }
}