#include <Wire.h>

#define DEV_ID 0x90 >> 1
#define TH 0xA1
#define TL 0xA2
#define THF B01000000
#define TLF B00100000

#define LED RED_LED

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


void setThreshold(byte reg, int temp) {
  if (reg == ACCESS_TH) {
    Wire.beginTransmission(DEV_ID);
    Wire.write(reg);                             // select temperature reg
    Wire.write(byte(temp));                        // set threshold
    Wire.write(0);                               // clear fractional bit
    Wire.endTransmission();
    delay(15);
  }
}

byte getReg(byte reg) {
  Wire.beginTransmission(DEV_ID);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(DEV_ID, 1);
  byte regVal = Wire.read();
  return regVal;
}

void checkTH(byte reg) {
  if (reg == ACCESS_TH) {
    byte value = getReg(reg);
    if (value == THF) {
      Led.toggle_on();
    } else if (value == TLF) {
      Led.toggle_off();
    }
  }
}

void setup() {
  Serial.begin(9600);

  Wire.begin();
  Wire.beginTransmission(DEV_ID);
  Wire.write(0xAC);
  Wire.write(0x02);
  Wire.beginTransmission(DEV_ID);
  Wire.write(0xEE);
  Wire.endTransmission();
  setThreshold(TH, 24);

}

TLed<LED> Led;

void loop() {
  int8_t firstByte;
  int8_t secondByte;
  float temp = 0;

  delay(1000);
  
  checkTH();
  Wire.beginTransmission(DEV_ID);
  Wire.write(0xAA);        // read temperature command
  Wire.endTransmission();
  Wire.requestFrom(DEV_ID, 2);

  if (Wire.available()) {
    firstByte = Wire.read();
    temp = firstByte;
  }
  if (Wire.available()) {
    secondByte = Wire.read();
    temp += 0.5;
  }

  Serial.println(temp);

}
