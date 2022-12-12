#include <Wire.h>

byte ADDRESS_SLAVE = 0X48; 
byte REGISTER_XY = 0X1F;
byte READ_LENGTH = 8;

int X0,X1,X_out;

void setup() 
{
 Wire.begin();
 Wire.setClock(400000); // set I2C 'full-speed'
 Serial.begin(9600);
}

void loop() 
{
   Wire.beginTransmission(ADDRESS_SLAVE);  
   Wire.write(REGISTER_XY);  // set register for read
   Wire.endTransmission(false); // false to not release the line

   Wire.requestFrom(ADDRESS_SLAVE,READ_LENGTH); // request bytes from register XY
   
   if(Wire.available())
   {
    X0 = Wire.read();
 //   X1 = Wire.read();
   }
   Serial.print ("X0=  ");
   Serial.println(X0);
//   Serial.print("   X1= ");
//   Serial.println(X1);
   
//   byte buff[READ_LENGTH];    
//   Wire.readBytes(buff, READ_LENGTH);
//   for (int i = 0; i < READ_LENGTH; i++) {
//     Serial.println(buff[i], HEX);
//   }
//   Serial.println();
//   delay(1000);
}
