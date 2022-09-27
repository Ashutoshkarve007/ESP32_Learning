#include <SoftwareSerial.h>
SoftwareSerial xbeeSerial(2,3); //RX, TX

void setup() {
   Serial.begin(9600);
   xbeeSerial.begin(9600);
}

void loop() {
   //Serial.println();
   if(xbeeSerial.available() > 0){
      
      Serial.print((char)xbeeSerial.read());
      
   }
}
