int SW = 2;
int is_switch_press = 0; // For detecting the switch press status
int debounce_delay = 300; //Debounce delay


void setup() {

  pinMode(SW, INPUT);
  Serial.begin(9600);

}


void loop() {

  is_switch_press = digitalRead(SW); // Reading the Switch press status
  
  if (is_switch_press == HIGH) {
    
    delay(debounce_delay); // debounce delay for button press
    
    if (is_switch_press == HIGH) {
      
      Serial.println("QUROLABS");
      
      delay(100);

      Serial.println("Hello");

      delay(100);

      Serial.println("from Ashutosh");

      Serial.println ("\n\r");

      Serial.println ("Thank You.");

      Serial.println ("\n\r");

    // is_switch_press = LOW;

    }

  }



}
