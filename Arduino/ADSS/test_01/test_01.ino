#include <Wire.h>

const byte ADDRESS = 0x48;
#define data_X0 0x1F

int X0,X1,X_out;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  delay (100);
  Wire.beginTransmission(72);
  Wire.write(8);  
  Wire.write(4);
  Wire.endTransmission(); 
}

void loop() {
  // put your main code here, to run repeatedly:
 
   Wire.beginTransmission(72);
   Wire.write(data_X0);
   
   Wire.endTransmission();

   Wire.requestFrom(72,2);


  if(Wire.available ())
  {
    X0 = Wire.read();
    X1 = Wire.read();
  }
   Serial.print ("X0=  ");
   Serial.println(X0);
   Serial.print("   X1= ");
   Serial.println(X1);
   
}
