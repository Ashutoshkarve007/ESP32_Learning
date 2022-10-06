#include <SoftwareSerial.h>
SoftwareSerial xbeeSerial(2, 3); //RX, TX
char reciveChar = 'x';

void setup() {
  Serial.begin(9600);
  xbeeSerial.begin(9600);
  pinMode(4, OUTPUT);            // Blue
  pinMode(6, OUTPUT);            // Orange
}

void loop() {

  if (xbeeSerial.available() > 0) {

    reciveChar = xbeeSerial.read();
  }
    Serial.println(reciveChar);
    delay(10);
    if (reciveChar == '+')
    {
      digitalWrite(4, HIGH);
      digitalWrite(6, LOW);
      reciveChar = 'b';
    }
    else if(reciveChar != '+') 
    {
      digitalWrite(6, HIGH);
      digitalWrite(4, LOW);
    }

}
