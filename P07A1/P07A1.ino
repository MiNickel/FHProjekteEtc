#define PAUSE 500

const uint8_t Button1 = PC_4;
const uint8_t Button2 = PC_5;
const uint8_t Piezo = PC_6;

const uint8_t beep = 3;

uint8_t buttonPushCounter = 0;

uint8_t buttonState1;
uint8_t buttonState2;

uint8_t currentState = 0;

/* Zustand 0 = 00, 1 = 01, 2 = 10,
  delay nach jedem Knopfdruck damit sich die Zustände nicht direkt
  mehrmals ändern*/

void setup() {
  pinMode(Piezo, OUTPUT);
  pinMode(Button1, INPUT);
  pinMode(Button2, INPUT);
  Serial.begin(9600);

}

void loop() {

  buttonState1 = digitalRead(Button1);
  buttonState2 = digitalRead(Button2);

  if (buttonState1 == HIGH && currentState == 0) {
    currentState = 2;
    delay(PAUSE);
  }
  else if (buttonState2 == HIGH && currentState == 0) {
    currentState = 1;
    delay(PAUSE);
  }
  else if (buttonState1 == HIGH && currentState == 2) {
    currentState = 0;
    delay(PAUSE);
  }
  else if (buttonState2 == HIGH && currentState == 2 ) {
    currentState = beep;
    digitalWrite(Piezo, HIGH);
  
    delay(PAUSE);
  }
  else if (buttonState1 == HIGH && currentState == 1) {
    currentState = beep;
    digitalWrite(Piezo, HIGH);
  
    delay(PAUSE);
  }
  else if (buttonState2 == HIGH && currentState == 1 ) {
    currentState = 0;

    delay(PAUSE);
  }
  else if (buttonState1 == HIGH && currentState == beep) {
    currentState = 1;
    digitalWrite(Piezo, LOW);
    delay(PAUSE);
  }
  else if (buttonState2 == HIGH && currentState == beep ) {
    currentState = 2;
    digitalWrite(Piezo, LOW);
    delay(PAUSE);
  }
  Serial.println(currentState); //Einsehen der Zustände
  

}
