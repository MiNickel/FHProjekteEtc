#define TW 500
#define TU 250
#define TG 500

const uint8_t Pedestrian_Green = PC_4;
const uint8_t Pedestrian_Red = PC_5;
const uint8_t Vehicle_Green = PC_6;
const uint8_t Vehicle_Yellow = PC_7;
const uint8_t Vehicle_Red = PD_6;

uint8_t state = 0;

template <const uint8_t PORT_NB>
class TLed {
  public:
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

      int returnValue = LOW;

      int currentState = digitalRead(PIN_NB);

      if (currentState != lastButtonState) {
        lastDebounceTime = millis();
      }

      if ((millis() - lastDebounceTime) > debounceDelay) {
        if (currentState != buttonState) {
          buttonState = currentState;
          if (buttonState == LOW) {
            returnValue = HIGH;
          }
        }
      }

      lastButtonState = currentState;

      return returnValue;
    }

  private:
    int buttonState;
    int lastButtonState;
    unsigned long lastDebounceTime;
    unsigned long debounceDelay;
};

TLed <Pedestrian_Green> p_Green;
TLed <Pedestrian_Red> p_Red;
TLed <Vehicle_Green> v_Green;
TLed <Vehicle_Yellow> v_Yellow;
TLed <Vehicle_Red> v_Red;
TButton <PUSH2> button;

void changeState() {
  if (state == 0) {
    v_Yellow.toggle_off();
    v_Red.toggle_off();
    v_Green.toggle_on();
    p_Red.toggle_on();
    Serial.println("z0: Fussgaengerampel: rot, Fahrzeugampel: gruen");
  } else if (state == 1) {
    Serial.println("z1: Fussgaengerampel: rot, Fahrzeugampel: gruen");
  } else if (state == 2) {
    Serial.println("z2: Fussgaengerampel: rot, Fahrzeugampel: gruen");
  } else if (state == 3) {
    v_Yellow.toggle_on();
    v_Green.toggle_off();
    Serial.println("z3: Fussgaengerampel: rot, Fahrzeugampel: gelb");
  } else if (state == 4) {
    v_Yellow.toggle_off();
    v_Red.toggle_on();
    Serial.println("z4: Fussgaengerampel: rot, Fahrzeugampel: rot");
  } else if (state == 5) {
    p_Red.toggle_off();
    p_Green.toggle_on();
    Serial.println("z5: Fussgaengerampel: gruen, Fahrzeugampel: rot");
  } else if (state == 6) {
    Serial.println("z6: Fussgaengerampel: gruen, Fahrzeugampel: rot");
  } else if (state == 7) {
    p_Red.toggle_on();
    p_Green.toggle_off();
    Serial.println("z7: Fussgaengerampel: rot, Fahrzeugampel: rot");
  } else if (state == 8) {
    v_Yellow.toggle_on();
    Serial.println("z8: Fussgaengerampel: rot, Fahrzeugampel: gelb-rot");
  }
}



void setup() {
  Serial.begin(9600);
  changeState();

}

void loop() {

  if (button.state()) {
    state++;
    changeState();
    delay(TW);

    state++;
    changeState();
    delay (TU);

    state++;
    changeState();
    delay(TU);

    state++;
    changeState();
    delay(TU);

    state++;
    changeState();
    delay(TG);

    state++;
    changeState();
    delay (TU);

    state++;
    changeState();
    delay(TU);

    state++;
    changeState();
    delay(TU);

    state = 0;
    changeState();

  }
}
