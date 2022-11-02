//#include <SPI.h>
//#include <Wire.h>
//#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//#define SDA 21
//#define SCL 22

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
SoftwareSerial xbeeSerial(16, 17); //RX, TX 2 3

double reciveChar = 'x';

void setup() {
  Serial.begin(9600);
  xbeeSerial.begin(9600);
  delay(10);

  pinMode(4, OUTPUT);            // Blue
  pinMode(5, OUTPUT);            // Orange

  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
  //  display.display();
  delay(500); // Pause for 2 seconds
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setRotation(0);
  display.clearDisplay();
  
}

void loop() {

  //display.clearDisplay();
  display.setCursor(0, 0);
  if (xbeeSerial.available() > 0) {
    display.println("Temperature : ");

    reciveChar = xbeeSerial.read();
  display.print(reciveChar);
 // display.print('167');
  display.print("C");
  Serial.println(reciveChar);
  }
  
 
//
//  if (reciveChar == '+')
//  {
//    digitalWrite(4, HIGH);
//    reciveChar = 'b';
//  }
//  else
//  {
//    digitalWrite(4, LOW);
//  }
 display.display();
//  delay(10);
}
