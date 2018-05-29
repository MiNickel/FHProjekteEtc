// Demo illustrating blinking led and reading of button.
// Led is finally turned off when button is pressed.

// define port for led output
const uint8_t LedPortOut = RED_LED;
// define pin for button input
const uint8_t ButtonPinIn = PC_4;
// define delay for blinking in ms
const uint32_t Delay = 2000;

uint8_t buttonPushCounter = 0;

//! LED handling class. Has disable() function for emergency stop.
//! Parameter (in): PORT_NB (output port for connected led)
template <const uint8_t PORT_NB>
class TLed {
  public:
    //! Constructor takes state (HIGH, LOW) only if given.
    //! Defaults: value for state = LOW, and is not disabled.
    TLed(const uint8_t f_ledState = HIGH)
      : m_ledState(f_ledState) {
      pinMode(PORT_NB, OUTPUT); // led is always output
      digitalWrite(PORT_NB, m_ledState); // set led to default state
    }
    //! If this led is disable, nothing happens, otherwise
    //! toggles state of led (from HIGH to LOW or from LOW to HIGH).
    void toggle() {

      if (buttonPushCounter % 2 == 0) {
        digitalWrite(PORT_NB, HIGH);
     
      } else {
        digitalWrite(PORT_NB, LOW);
        
      }
    }

    //! Turn led finally off (emergency stop), state is set LOW, functionality off.
    void off() {
      m_ledState = LOW;
      digitalWrite(PORT_NB, m_ledState); // set led to current state
    }
  private:
    uint8_t m_ledState; // current state of led
    // disable flag (on if led is finally turned off)
};

template <const uint8_t PORT_NB2>
class TButton {
  public:
    TButton() {
      pinMode(PORT_NB2, INPUT);
    }

    void state() {
      buttonState = digitalRead(PORT_NB2);

      if (buttonState != lastButtonState) {

        if (buttonState == HIGH) {

          buttonPushCounter++;
          
          Serial.print("number of button pushes:  ");
          Serial.println(buttonPushCounter);
        }
        
      }

      lastButtonState = buttonState;

    }
  private:
    uint8_t buttonState;
    uint8_t lastButtonState;


};

//....TODO: INSERT CODE FOR CLASS TBUTTON....

// global instances for led output
TLed<LedPortOut> Led;
// and for button pin
TButton<ButtonPinIn> Button;

void setup() {
  Serial.begin(9600);
}

void loop() {


  // if emergency stop, turn led off

  Button.state();
  Led.toggle();

}
// wait







