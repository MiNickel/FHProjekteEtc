#define LED RED_LED

void setup() {
  // initialize the digital pin as an output.
  pinMode(LED, OUTPUT); 
}

void S() {
  digitalWrite(LED, HIGH);
  delay(200);
  digitalWrite(LED, LOW);
  delay(200);
  digitalWrite(LED, HIGH);
  delay(200);
  digitalWrite(LED, LOW);
  delay(200);
  digitalWrite(LED, HIGH);
  delay(200);
  digitalWrite(LED, LOW);
  delay(600);
}
void O() {
  digitalWrite(LED, HIGH);
  delay(600);
  digitalWrite(LED, LOW);
  delay(200);
  digitalWrite(LED, HIGH);
  delay(600);
  digitalWrite(LED, LOW);
  delay(200);
  digitalWrite(LED, HIGH);
  delay(600);
  digitalWrite(LED, LOW);
  delay(600);
}
void SOS() {
  S();
  O();
  S(); 
}

void loop() {
  // put your main code here, to run repeatedly: 
  SOS();
  delay(3000);
}
