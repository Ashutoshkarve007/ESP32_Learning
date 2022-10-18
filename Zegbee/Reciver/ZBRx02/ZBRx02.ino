#include <SoftwareSerial.h>
SoftwareSerial xbeeSerial(16, 17); //RX, TX 2 3
char reciveChar = 'x';

void setup() {
  Serial.begin(9600);
  xbeeSerial.begin(9600);
  
  pinMode(4, OUTPUT);            // Blue
  pinMode(5, OUTPUT);            // Orange

  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
}

void loop() {

  if (xbeeSerial.available() > 0) {

    reciveChar = xbeeSerial.read();
  }
  Serial.println(reciveChar);

  if (reciveChar == '+')
  {
    digitalWrite(4, HIGH);
    reciveChar = 'b';
  }
  else
  {
    digitalWrite(4, LOW);
  }
  delay(10);
}
