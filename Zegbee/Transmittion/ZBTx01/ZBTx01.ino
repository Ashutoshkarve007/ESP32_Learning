#include <SoftwareSerial.h>
SoftwareSerial xbeeSerial(16,17); //RX, TX

void setup() {
   Serial.begin(9600);
   xbeeSerial.begin(9600);
   pinMode(4, OUTPUT);
   pinMode(15, OUTPUT);
   digitalWrite(4, HIGH);
   digitalWrite(15, HIGH);
}

void loop() {


 
      xbeeSerial.write("+");
//      delay(100);
//      digitalWrite(4,HIGH);
//      digitalWrite(6,HIGH);

}
