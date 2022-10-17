// include the library code:
#include <LiquidCrystal.h>
int myCounter = 0; // declare counter variable and set to zero 
int flag = 0; // declare flag 

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Person Counter!");
  lcd.setCursor(0,1);
  lcd.print(0);
}

void loop() {
  // set the cursor to column 0, line 1
  lcd.setCursor(0, 1);
  
  if(analogRead(A0) < 900)
  {
    flag = 1;
  }
 
  if(analogRead(A0) > 900 && flag == 1)
  {
    myCounter++;
    lcd.print(myCounter);
    flag = 0; 
  }
}

