#define trigger_pin 12
#define Echo_pin 14

long duration;
int distance;

void setup() {

  pinMode(trigger_pin, OUTPUT); // configure the trigger_pin(D9) as an Output
  pinMode(Echo_pin, INPUT);     // configure the Echo_pin(D11) as an Input
  Serial.begin(9600);           // Enable the serial with 9600 baud rate

}

void loop() {

  digitalWrite(trigger_pin, LOW); //set trigger signal low for 2us
  delayMicroseconds(2);

  digitalWrite(trigger_pin, HIGH);  // make trigger pin active high
  delayMicroseconds(10);            // wait for 10 microseconds
  digitalWrite(trigger_pin, LOW);   // make trigger pin active low

  duration = pulseIn(Echo_pin, HIGH); // save time duration value in "duration variable
  distance = duration * 0.034 / 2;    //Convert pulse duration into distance

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(1000);
}
