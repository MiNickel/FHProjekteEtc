#include <Wire.h>

#define DEV_ID 0x90 >> 1
#define TH 0xA1                         
#define TL 0xA2 
#define THF B01000000

void setThreshold(byte reg, int temp)
{
 if (reg == ACCESS_TH) {
   Wire.beginTransmission(DEV_ID);
   Wire.write(reg);                             // select temperature reg
   Wire.write(byte(temp));                        // set threshold
   Wire.write(0);                               // clear fractional bit
   Wire.endTransmission();
   delay(15);
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

void loop() {
  int8_t firstByte;
  int8_t secondByte;
  float temp = 0;

  delay(1000);                                

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
