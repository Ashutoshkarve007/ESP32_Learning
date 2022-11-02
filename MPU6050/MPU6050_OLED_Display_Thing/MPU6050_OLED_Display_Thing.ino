#include <WiFi.h>
#include "ThingSpeak.h"

#include <SoftwareSerial.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
//SoftwareSerial xbeeSerial(2,3); //RX, TX

const char* ssid = "Embedded";
const char* password = "1234567890@";

WiFiServer server(80);
WiFiClient client;

unsigned long lastTime = 0;
unsigned long timerDelay = 10000;

unsigned long myChannelNumber = 1;
const char * myWriteAPIKey = "R0B9K60OJHD4R3AR";

float accX, accY, accZ;

void setup() {
  Serial.begin(115200);
  // xbeeSerial.begin(9600);
  delay(10);

  //pinMode(4, OUTPUT);            // Blue
  // pinMode(5, OUTPUT);            // Orange


  // while (!Serial);
  Serial.println("MPU6050 OLED demo");

  if (!mpu.begin()) {
    Serial.println("Sensor init failed");
    while (1)
      yield();
  }
  Serial.println("Found a MPU-6050 sensor");

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
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

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Print local IP address and start web server

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();

  //----nitialize

  ThingSpeak.begin(client); // Initialize ThingSpeak



  //      digitalWrite(4,HIGH);
  //      digitalWrite(5,HIGH);

}

void loop() {


  // Connect or reconnect to WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect");
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, password);
      delay(5000);
    }
    Serial.println("\nConnected.");
  }

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

//  display.clearDisplay();
//  display.setCursor(0, 0);

  ThingSpeak.setField(1, accX);
  ThingSpeak.setField(2, accY);
  ThingSpeak.setField(3, accZ);
  ThingSpeak.setField(4, temp.temperature);

//  Serial.print("Accelerometer ");
//  Serial.print("X: ");
//  Serial.print(a.acceleration.x, 1);
//  Serial.print(" m/s^2, ");
//  Serial.print("Y: ");
//  Serial.print(a.acceleration.y, 1);
//  Serial.print(" m/s^2, ");
//  Serial.print("Z: ");
//  Serial.print(a.acceleration.z, 1);
//  Serial.println(" m/s^2");


  accX = a.acceleration.x;
  accY = a.acceleration.y;
  accZ = a.acceleration.z;

//
//  Serial.print("Gyroscope ");
//  Serial.print("X: ");
//  Serial.print(g.gyro.x, 1);
//  Serial.print(" rps, ");
//  Serial.print("Y: ");
//  Serial.print(g.gyro.y, 1);
//  Serial.print(" rps, ");
//  Serial.print("Z: ");
//  Serial.print(g.gyro.z, 1);
//  Serial.println(" rps");
//
//  display.println("Gyroscope - rps");
//  display.print(g.gyro.x, 1);
//  display.print(", ");
//  display.print(g.gyro.y, 1);
//  display.print(", ");
//  display.print(g.gyro.z, 1);
//  display.println("");

  //display.println("by Ashutosh");

  int x = ThingSpeak.writeFields(1, "R0B9K60OJHD4R3AR");

  if (x == 200) {
    Serial.println("Channel update successful.");
  }
  else {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
//  display.println("Accelerometer - m/s^2");
//  display.print(a.acceleration.x, 1);
//  display.print(", ");
//  display.print(a.acceleration.y, 1);
//  display.print(", ");
//  display.print(a.acceleration.z, 1);
//  display.println("");
//  display.display();
  
  // delay(100);
}
