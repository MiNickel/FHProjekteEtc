//Wartezeit
#define TW 1000
#define TU 500
#define TG 1000
#define PUSH_BUTTON PUSH2

//Ampelelemente
const uint8_t F_GREEN = PC_4;
const uint8_t F_RED = PC_5;
const uint8_t V_GREEN = PC_6;
const uint8_t V_YELLOW = PC_7;
const uint8_t V_RED = PD_6;

template <const uint8_t PORT_NB>
class TLed {
  public:
    //! Constructor takes state (HIGH, LOW) only if given.
    //! Defaults: value for state = LOW, and is not disabled.
    TLed(const uint8_t f_ledState = LOW)
      : m_ledState(f_ledState), m_disabled(false) {
      pinMode(PORT_NB, OUTPUT); // led is always output
      digitalWrite(PORT_NB, m_ledState); // set led to default state
    }
    //! If this led is disable, nothing happens, otherwise
    //! toggles state of led (from HIGH to LOW or from LOW to HIGH).
    void toggle_on() {
      if (m_disabled) // somehow no longer active
        return;
      m_ledState = HIGH;

      digitalWrite(PORT_NB, m_ledState); // set led to current state
    }
    void toggle_off() {
      if (m_disabled) // somehow no longer active
        return;
      m_ledState = LOW;

      digitalWrite(PORT_NB, m_ledState); // set led to current state
    }
    //! Turn led finally off (emergency stop), state is set LOW, functionality off.
    void off() {
      m_disabled = true;
      m_ledState = LOW;
      digitalWrite(PORT_NB, m_ledState); // set led to current state
    }
  private:
    uint8_t m_ledState; // current state of led
    bool m_disabled; // disable flag (on if led is finally turned off)
};


template <const uint8_t PIN_NB>
class TButton {
  public:
    TButton()
      : buttonState(LOW), lastButtonState(LOW), lastDebounceTime(0), debounceDelay(50) {
      pinMode(PIN_NB, INPUT);
    }

    uint8_t state() {
      // prepare the default return value
      int returnValue = LOW;
      // read the state of the switch into a local variable
      int reading = digitalRead(PIN_NB);
         // If the switch changed, due to noise or pressing:
      if (reading != lastButtonState) {
        // reset the debouncing timer
        lastDebounceTime = millis();
      }

      if ((millis() - lastDebounceTime) > debounceDelay) {
        // if the button state has changed:
        if (reading != buttonState) {
          buttonState = reading;
          // only return HIGH if the new button state is HIGH (i.e. rising edge)
          if (buttonState == LOW) { //PUSH2 is unused HIGH
            returnValue = HIGH;
          }
        }
      }

      // save the reading. Next time through the loop, it'll be the lastButtonState:
      lastButtonState = reading;

      return returnValue;
    }

  private:
    int buttonState;                 // the current reading from the input pin
    int lastButtonState;             // the previous reading from the input pin
    unsigned long lastDebounceTime;  // the last time the output pin was toggled
    unsigned long debounceDelay;     // the debounce time; increase if the output flickers
};

TLed <F_GREEN> fGreen;
TLed <F_RED> fRed;
TLed <V_GREEN> vGreen;
TLed <V_YELLOW> vYellow;
TLed <V_RED> vRed;
TButton <PUSH2> button;


//Symbolisiert den Aktuellen Zustand, kein Einfluss auf die Programm-Funktion
uint8_t state = 0;
void printZustand() {
  switch (state) {
    case 0: Serial.println ("Zustand 0) (Default Zustand) V=Gruen F=Rot");
      break;
    case 1: Serial.println ("Zustand 1) V=Gruen F=Rot Knopf gedrueckt");
      break;
    case 2: Serial.println ("Zustand 2) V=Gruen F=Rot T(w) abgelaufen ");
      break;
    case 3: Serial.println ("Zustand 3) V=Gelb F=Rot T(u) abgelaufen");
      break;
    case 4: Serial.println ("Zustand 4) V=Rot F=Rot");
      break;
    case 5: Serial.println ("Zustand 5) V=Rot F=Gruen");
      break;
    case 6: Serial.println ("Zustand 6) V=Rot F=Gruen T(g) abgelaufen" );
      break;
    case 7: Serial.println ("Zustand 7) V=Rot F=Rot");
      break;
    case 8: Serial.println ("Zustand 8) V=Gelb-Rot F=Rot");
      break;
  }
}

void setup() {
  Serial.begin(9600);
  vGreen.toggle_on();
  fRed.toggle_on();
  printZustand();
  
}



void loop() {

  //Aktuell Z0

  if (button.state()) { //Wenn Button SW2 gedrueckt wird
    state++;
    printZustand();
    //Aktuell Z1
    delay(TW);
    state++;
    printZustand();
    //Aktuell Z2
    delay (TU);
    state++;
    printZustand();
    //Aktuell Z3
    vYellow.toggle_on();
    vGreen.toggle_off();
    delay(TU);
    state++;
    printZustand();
    //Aktuell Z4
    vYellow.toggle_off();
    vRed.toggle_on();
    delay(TU);
    state++;
    printZustand();
    //Aktuell Z5
    fRed.toggle_off();
    fGreen.toggle_on();
    delay(TG);
    state++;
    printZustand();
    //Aktuell Z6
    delay (TU);
    state++;
    printZustand();
    //Aktuell Z7
    fRed.toggle_on();
    fGreen.toggle_off();
    delay(TU);
    state++;
    printZustand();
    //Aktuell Z8
    vYellow.toggle_on();
    delay(TU);
    state = 0;
    printZustand();
    //Aktuell Z0
    vYellow.toggle_off();
    vRed.toggle_off();
    vGreen.toggle_on();
    fRed.toggle_on();
  }
}
