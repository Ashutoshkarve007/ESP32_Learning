#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>

#define BUTTON_PIN 4

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

int IRSensor = 2; // connect ir sensor to arduino pin 2
int flag = 0;
int myCounter = 0;

struct button {
  byte pressed = 0;
};

button button;


bool isButtonPressed(int pin)
{
  return digitalRead(pin) == 0;
}

void setup()
{

  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode (IRSensor, INPUT); // sensor pin INPUT

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
 // display.display();
  delay(500); // Pause for 2 seconds
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setRotation(0);

  

}

void loop()
{
  int statusSensor = digitalRead (IRSensor);
  button.pressed = isButtonPressed(BUTTON_PIN);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("++++++QuroLabs+++++++");
  display.println("+                   +");
  display.print  ("+    Counter :");
  display.print(myCounter);
  
  if(myCounter < 10)
  {
    display.print("     +");
  }
  else if(myCounter >= 10 && myCounter < 100)
  {
    display.print("    +");  
  }
  else if(myCounter >= 100)
  {
    display.print("   +");
  }
//  display.println("+                   +");
  display.println("+++++++++++++++++++++");
  if (statusSensor == 1)
  {
    flag = 1;
  }

  if (!statusSensor && flag == 1)
  {
    myCounter++;
    Serial.println(myCounter);

    flag = 0;
  }
  
  if (button.pressed) {
    Serial.println("Button pressed");
//    display.println(" ");
//    display.println(" ");
//    display.println(" ");
//    display.print("Reset Value");
    myCounter = 0;
  } 
  display.display();
  delay(100);
}
