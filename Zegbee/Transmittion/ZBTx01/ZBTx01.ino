#include <SoftwareSerial.h>
SoftwareSerial xbeeSerial(2,3); //RX, TX

void setup() {
   Serial.begin(9600);
   xbeeSerial.begin(9600);
   pinMode(4, OUTPUT);
   pinMode(6, OUTPUT);
}

void loop() {


 
      xbeeSerial.write("+");
      delay(100);
      digitalWrite(4,HIGH);
      digitalWrite(6,HIGH);

}
