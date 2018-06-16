

const uint8_t Button1 = PC_4;
const uint8_t Button2 = PC_5;
const uint8_t Piezo = PC_6;

const uint8_t beep = 3;

uint8_t buttonPushCounter = 0;

uint8_t buttonState1;
uint8_t buttonState2;

uint8_t bCounter = 0;
uint8_t dCounter = 0;

uint8_t currentState = 0;


void setup() {
  pinMode(Piezo, OUTPUT);
  pinMode(Button1, INPUT);
  pinMode(Button2, INPUT);
  Serial.begin(9600);

}

void loop() {

  buttonState1 = digitalRead(Button1);
  buttonState2 = digitalRead(Button2);

  if (buttonState1 == HIGH && currentState == 0 && bCounter == 0) {
    currentState = 2;
    bCounter++;
    delay(1000);
  }
  else if (buttonState2 == HIGH && currentState == 0 && dCounter == 0) {
    currentState = 1;
    dCounter++;
    delay(1000);
  }
  else if (buttonState1 == HIGH && currentState == 2 && bCounter == 1) {
    currentState = 0;
    bCounter--;
    delay(1000);
  }
  else if (buttonState2 == HIGH && currentState == 2 && dCounter == 0) {
    currentState = beep;
    digitalWrite(Piezo, HIGH);
    dCounter++;
    delay(1000);
  }
  else if (buttonState1 == HIGH && currentState == 1 && bCounter == 0) {
    currentState = beep;
    digitalWrite(Piezo, HIGH);
    bCounter++;
    delay(1000);
  }
  else if (buttonState2 == HIGH && currentState == 1 && dCounter == 1) {
    currentState = 0;
    dCounter--;
    delay(1000);
  }
  else if (buttonState1 == HIGH && currentState == beep && bCounter == 1) {
    currentState = 1;
    digitalWrite(Piezo, LOW);
    bCounter--;
    delay(1000);
  }
  else if (buttonState2 == HIGH && currentState == beep && dCounter == 1) {
    currentState = 2;
    digitalWrite(Piezo, LOW);
    dCounter--;
    delay(1000);
  }
  Serial.println(currentState);

  /* buttonState = digitalRead(Button1);
    if (buttonState == HIGH) {
     digitalWrite(Piezo, HIGH);
     Serial.println("HIGH");
    }
    buttonState = digitalRead(Button2);
    if (buttonState == HIGH) {
     digitalWrite(Piezo, LOW);
     Serial.println("LOW");
    } */

}
