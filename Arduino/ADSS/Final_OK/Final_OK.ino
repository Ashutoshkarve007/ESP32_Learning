#include <Wire.h> // specify use of Wire.h library
#define ADDRESS 0x48

unsigned int val = 0;
byte writeBuf[3];
byte buffer[3];

const float VPS = 4.096 / 32768.0; // volts per step

void setup()   {

  Serial.begin(9600); 
  Wire.begin(); // begin I2C

  writeBuf[0] = 1;    // config register is 1
  writeBuf[1] = 0b11010010; // 0xC2 single shot off

  writeBuf[2] = 0b10000101; // bits 7-0  0x85

  Wire.beginTransmission(ADDRESS);  // ADC 
  Wire.write(writeBuf[0]); 
  Wire.write(writeBuf[1]);
  Wire.write(writeBuf[2]);  
  Wire.endTransmission();  

  delay(500);

}  // end setup

void loop() {

  buffer[0] = 0; // pointer
  Wire.beginTransmission(ADDRESS);  // DAC
  Wire.write(buffer[0]);  // pointer
  Wire.endTransmission();

  Wire.requestFrom(ADDRESS, 2);
  buffer[1] = Wire.read(); 
  buffer[2] = Wire.read();
  Wire.endTransmission();  

  // convert display results
  val = buffer[1] << 8 | buffer[2]; 

  if (val > 32768) val = 0;

//  Serial.println(val * VPS);
  Serial.println(val);
  
  delay(200);

}
