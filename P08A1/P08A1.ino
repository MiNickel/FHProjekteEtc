//Wartezeit
#define TW 500
#define TU 250
#define TG 500
#define PUSH_BUTTON PUSH2

const uint8_t Pedestrian_Green = PC_4;
const uint8_t Pedestrian_Red = PC_5;
const uint8_t Vehicle_Green = PC_6;
const uint8_t Vehicle_Yellow = PC_7;
const uint8_t Vehicle_Red = PD_6;

uint8_t state = 0;

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
      if (m_disabled) {
        return; // somehow no longer active
      }
        
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

void printZustand() {
  if (state == 0) {
    Serial.println("z0: Fußgängerampel: rot, Fahrzeugampel: grün");
  } else if (state == 1) {
    Serial.println("z1: Fußgängerampel: rot, Fahrzeugampel: grün");
  } else if (state == 2) {
    Serial.println("z2: Fußgängerampel: rot, Fahrzeugampel: grün");
  } else if (state == 3) {
    Serial.println("z3: Fußgängerampel: rot, Fahrzeugampel: gelb");
  } else if (state == 4) {
    Serial.println("z4: Fußgängerampel: rot, Fahrzeugampel: rot");
  } else if (state == 5) {
    Serial.println("z5: Fußgängerampel: grün, Fahrzeugampel: rot");
  } else if (state == 6) {
    Serial.println("z6: Fußgängerampel: grün, Fahrzeugampel: rot");
  } else if (state == 7) {
    Serial.println("z7: Fußgängerampel: rot, Fahrzeugampel: rot");
  } else if (state == 8) {
    Serial.println("z8: Fußgängerampel: rot, Fahrzeugampel: gelb-rot");
  }
}

TLed <Pedestrian_Green> p_Green;
TLed <Pedestrian_Red> p_Red;
TLed <Vehicle_Green> v_Green;
TLed <Vehicle_Yellow> v_Yellow;
TLed <Vehicle_Red> v_Red;
TButton <PUSH2> button;

void setup() {
  Serial.begin(9600);
  v_Green.toggle_on();
  p_Red.toggle_on();
  printZustand();
  
}



void loop() {

  if (button.state()) { 
    state++;
    printZustand();
    delay(TW);
    state++;
    printZustand();
    delay (TU);
    state++;
    printZustand();
    v_Yellow.toggle_on();
    v_Green.toggle_off();
    delay(TU);
    state++;
    printZustand();
    v_Yellow.toggle_off();
    v_Red.toggle_on();
    delay(TU);
    state++;
    printZustand();
    p_Red.toggle_off();
    p_Green.toggle_on();
    delay(TG);
    state++;
    printZustand();
    delay (TU);
    state++;
    printZustand();
    p_Red.toggle_on();
    p_Green.toggle_off();
    delay(TU);
    state++;
    printZustand();
    v_Yellow.toggle_on();
    delay(TU);
    state = 0;
    printZustand();
    v_Yellow.toggle_off();
    v_Red.toggle_off();
    v_Green.toggle_on();
    p_Red.toggle_on();
  }
}
