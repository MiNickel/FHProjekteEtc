#define LED RED_LED

const uint8_t ButtonSwitch = PC_4;
const uint8_t ButtonOutput = PC_5;
const uint8_t Piezo = PC_6;

const unsigned int WpM = 5;
const unsigned int DIT = 1200/WpM;
const unsigned int DAH = 3*DIT;

char inputText[128];
boolean stringComplete = false;

void setup() {
  Serial.begin(9600);
  pinMode(Piezo, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(ButtonSwitch, INPUT);
  pinMode(ButtonOutput, INPUT);

}

void loop() {
  if (stringComplete) {
    Serial.println(inputText);
    size_t n = sizeof(inputText);
    morseAll();
    memset(&inputText[0], 0, sizeof(inputText));
    stringComplete = false;
  }

}

void morseAll() {
  for (int i = 0; i < sizeof(inputText); i++) {
    switch (inputText[i]) {
      case 'A':
        morseA();
        break;
      case 'B':
        morseB();
        break;
      case 'C':
        morseC();
        break;
      case 'D':
        morseD();
        break;
      case 'E':
        morseE();
        break;
      case 'F':
        morseF();
        break;
      case 'G':
        morseG();
        break;
      case 'H':
        morseH();
        break;
      case 'I':
        morseI();
        break;
      case 'J':
        morseJ();
        break;
      case 'K':
        morseK();
        break;
      case 'L':
        morseL();
        break;
      case 'M':
        morseM();
        break;
      case 'N':
        morseN();
        break;
      case 'O':
        morseO();
        break;
      case 'P':
        morseP();
        break;
      case 'Q':
        morseQ();
        break;
      case 'R':
        morseR();
        break;
      case 'S':
        morseS();
        break;
      case 'T':
        morseT();
        break;
      case 'U':
        morseU();
        break;
      case 'V':
        morseV();
        break;
      case 'W':
        morseW();
        break;
      case 'X':
        morseX();
        break;
      case 'Y':
        morseY();
        break;
      case 'Z':
        morseZ();
        break;
      case ' ':
        halt();
        break;
      //If there is an undefined symbol in the array, the LED will hyperventilate().
      default:
        hyperventilate();
    }
    pause();
  }
}

void morseA() {
  dit();
  dah();
}

void morseB() {
  dah();
  dit();
  dit();
  dit();
}

void morseC() {
  dah();
  dit();
  dah();
  dit();
}

void morseD() {
  dah();
  dit();
  dit();
}

void morseE() {
  dit();
}

void morseF() {
  dit();
  dit();
  dah();
  dit();
}

void morseG() {
  dah();
  dah();
  dit();
}

void morseH() {
  dit();
  dit();
  dit();
  dit();
}

void morseI() {
  dit();
  dit();
}

void morseJ() {
  dit();
  dah();
  dah();
  dah();
}

void morseK() {
  dah();
  dit();
  dah();
}

void morseL() {
  dit();
  dah();
  dit();
  dit();
}

void morseM() {
  dah();
  dah();
}

void morseN() {
  dah();
  dit();
}

void morseO() {
  dah();
  dah();
  dah();
}

void morseP() {
  dit();
  dah();
  dah();
  dit();
}

void morseQ() {
  dah();
  dah();
  dit();
  dah();
}

void morseR() {
  dit();
  dah();
  dit();
}

void morseS() {
  dit();
  dit();
  dit();
}

void morseT() {
  dah();
}

void morseU() {
  dit();
  dit();
  dah();
}

void morseV() {
  dit();
  dit();
  dit();
  dah();
}

void morseW() {
  dit();
  dah();
  dah();
}

void morseX() {
  dah();
  dit();
  dit();
  dah();
}

void morseY() {
  dah();
  dit();
  dah();
  dah();
}

void morseZ() {
  dah();
  dah();
  dit();
  dit();
}

void dit () {
  digitalWrite(LED, HIGH);
  delay(DIT);
  digitalWrite(LED, LOW);
  delay(DIT);
}
void dah () {
  digitalWrite(LED, HIGH);
  delay(DAH);
  digitalWrite(LED, LOW);
  delay(DIT);
}

void pause() {
  delay(DAH);
}

void halt() {
  delay(7*DIT);
}

void hyperventilate() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED, HIGH);
    delay(80);
    digitalWrite(LED, LOW);
    delay(80);
  }
}

  void serialEvent() {
    while (Serial.available()) {
      Serial.readBytes(inputText, 128);
      stringComplete = true;
    }
  }

