#define no_debug_print                                               // manages most of the print and println debug, not all but most

#if defined debug_print
   #define debug_begin(x)        Serial.begin(x)
   #define debug(x)                   Serial.print(x)
   #define debugln(x)                 Serial.println(x)
#else
   #define debug_begin(x)
   #define debug(x)
   #define debugln(x)
#endif


const int led_upperEnd = 2;
const int led_dimm = 3;
const int led_lowerEnd = 4;
const int button1 = 5;
int dimm_led_power = 0;

const int dimm_maxVal = 255;
const int dimm_minVal = 0;
bool dimmer_is_rising = true;
int buttonState = 0;

void setup() {
  debug_begin(9600);

  pinMode(led_upperEnd, OUTPUT);
  pinMode(led_dimm, OUTPUT);
  pinMode(led_lowerEnd, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
}

// Die Helligkeit der LED ändert nach oben oder unten, solange der Knopf gedrückt wird
// Am unteren Limit leuchtet die "led_lowerEnd"
// Am oberen Limit leuchtet die "led_upperEnd"

void loop() {
  buttonState = !digitalRead(button1);

  debugln("Button " + String(buttonState) + " / Led Power " + String(dimm_led_power));

  // HALT STOPP!
  // Prüfe, ob der Button gedrückt ist, sonst unternehme ich nix
  if (buttonState == HIGH) {  
    if (dimmer_is_rising && dimm_led_power < dimm_maxVal) {
      dimm_led_power++;
    } else if (!dimmer_is_rising && dimm_led_power > dimm_minVal) {
      dimm_led_power--;
    }

    if (dimm_led_power >= dimm_maxVal) {
      dimmer_is_rising = false;
    } else if (dimm_led_power <= dimm_minVal) {
      dimmer_is_rising = true;
    }
  }

  // LED dimmen mit PWM
  analogWrite(led_dimm, dimm_led_power);  
  if(dimm_led_power <= dimm_minVal){
    digitalWrite(led_lowerEnd, HIGH);
    delay(1000);
  }else{
    digitalWrite(led_lowerEnd, LOW);
  }
  if(dimm_led_power >= dimm_maxVal){
    digitalWrite(led_upperEnd, HIGH);
    delay(1000);
  }else{
    digitalWrite(led_upperEnd, LOW);
  }

  // Kleiner Delay, um das Dimmen sanfter zu machen
  // Geht am besten, wenn debug_print nicht aktiv ist
  delay(10); 
}
