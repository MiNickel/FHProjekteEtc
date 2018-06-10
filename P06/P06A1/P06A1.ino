// our working number
volatile uint8_t number = 1;
// baudrate for serial communication
const int baudRate = 9600;
// initialize Serial
void setup() {
  Serial.begin(baudRate);
}
// main loop
void loop() {
  // print number
  Serial.println(number);
  asm volatile(
    //TODO: insert program here
    "mov r4, %[value]\n\t"
    "cmp r4, #128\n\t"
    "ite eq\n\t"
    "moveq r4, #1\n\t"
    "addne r4, r4\n\t"
    "mov %[value], r4\n\t"
    : [value] "r+" (number)
    :
    : "r4", "memory", "cc"
  );
}

