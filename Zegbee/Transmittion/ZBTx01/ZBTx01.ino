#include <SoftwareSerial.h>
SoftwareSerial xbeeSerial(16,17); //RX, TX

void setup() {
   Serial.begin(115200);
   xbeeSerial.begin(115200);
   pinMode(4, OUTPUT);
   pinMode(5, OUTPUT);
   digitalWrite(4, HIGH);
   digitalWrite(5, HIGH);
}

void loop() {


 
      xbeeSerial.write("+");
//      delay(100);
//      digitalWrite(4,HIGH);
//      digitalWrite(6,HIGH);

}
