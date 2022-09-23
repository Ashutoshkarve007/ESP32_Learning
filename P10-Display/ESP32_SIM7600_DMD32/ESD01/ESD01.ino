//   "m": "QuroLabs","g":"1","a":"4","x":"25","y":"7","f":"1"

#include "secrets.h"
#include "declarations.h"
#include <DMD32.h>
#include <SoftwareSerial.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <EEPROM.h>
#include <ArduinoJson.h>
#include <WiFi.h>

/*            Fonts               */
#include "fonts/SystemFont5x7.h"
#include "fonts/Arial_black_16.h"
#include "fonts/Arial_38b.h"
#include "fonts/Arial_Black_16_ISO_8859_1.h"
#include "fonts/Arial_Black21.h"
#include "fonts/Arial14.h"
#include "fonts/BodoniMTBlack24.h"
#include "fonts/Comic24.h"
#include "fonts/Droid_Sans_24.h"
#include "fonts/Tahoma_32.h"
//new fonts added................//
#include "fonts/BigNumber.h"
#include "fonts/DejaVuSans9.h"
#include "fonts/DejaVuSansBold9.h"

#define DISPLAYS_ACROSS 4
#define DISPLAYS_DOWN 2

/*           P10 pins              */
#define PIN_DMD_nOE 22          //22       //4    // D22 active low Output Enable, setting this low lights all the LEDs in the selected rows. Can pwm it at very high frequency for brightness control.
#define PIN_DMD_A 19            //19       //13   // D19  default is 15   
#define PIN_DMD_B 21            //21       //12   // D21
#define PIN_DMD_CLK 18          //18       //18   // D18_SCK  is SPI Clock if SPI is used   R39
#define PIN_DMD_SCLK  2         //2        //14   // D02
#define PIN_DMD_R_DATA  23      //23       //23   // D23_MOSI is SPI Master Out if SPI is used

DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

const char* Data = "";
const char* animation = "";
const char* positionx = "";
const char* positiony = "";
const char* graphics = "";
const char* fontm = "";

const char* s = "";
byte g;
int p = 0;
int q = 0;

//Variables
int i = 0;
int statusCode;
const char* ssid = "Embedded";
const char* passphrase = "1234567890@";
String st;
String content;
String esid = "";
String epass = "";


//Function Decalration
bool testWifi(void);
void launchWeb(void);
void setupAP(void);

//Establishing Local Server at port 80
WebServer server(80);

hw_timer_t * timer = NULL;

void IRAM_ATTR triggerScan()
{
  dmd.scanDisplayBySPI();
}
void connectAWS()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.setServer(AWS_IOT_ENDPOINT, 8883);

  // Create a message handler
  client.setCallback(messageHandler);

  Serial.println("Connecting to AWS IOT");

  while (!client.connect(THINGNAME))
  {
    Serial.print(".");
    delay(100);
  }

  if (!client.connected())
  {
    Serial.println("AWS IoT Timeout!");
    return;
  }

  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

  Serial.println("AWS IoT Connected!");
}

void publishMessage()
{
  StaticJsonDocument<200> doc;
  doc["message"] = "Hello From ESP32";
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client

  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

void messageHandler(char* topic, byte* payload, unsigned int length)
{
  Serial.print("incoming: ");
  Serial.println(topic);

  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  Data = doc["m"];
  Serial.println(Data);

  graphics = doc["g"];
  Serial.println(graphics);

  animation = doc["a"];
  Serial.println(animation);

  positionx = doc["x"];
  Serial.println(positionx);

  positiony = doc["y"];
  Serial.println(positiony);

  fontm = doc["f"];
  Serial.println(fontm);

}
void hardwareTimer()
{
  uint8_t cpuClock = ESP.getCpuFreqMHz();
  timer = timerBegin(0, cpuClock, true);
  timerAttachInterrupt(timer, &triggerScan, true);
  timerAlarmWrite(timer, 300, true);
  timerAlarmEnable(timer);
}

3
void setup(void)
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("Disconnecting current wifi connection");
  
  delay(10);
  connectAWS();
  publishMessage();
  delay(1000);
  hardwareTimer();
  delay(1000);
  dmd.clearScreen( true );
  Data = "123Welcome123";
  int x = 1;
  int y = 5;
  int p = 0;
  int q = 32;
  g = GRAPHICS_NORMAL;
  delay(200);
}

void loop(void)
{
  client.loop();
  fontmode();
  graphicsmode();
  switchcommands();

}
void fontmode()
{
  int fm = atoi(fontm);
  switch (fm)
  {
    case 1:
      dmd.selectFont(SystemFont5x7);
      p = 0;
      q = 8;
      break;
    case 2:
      dmd.selectFont(DejaVuSans9);
      p = 0;
      q = 9;
      break;
    case 3:
      dmd.selectFont(DejaVuSansBold9);
      p = 0;
      q = 9;
      break;
    case 4:
      dmd.selectFont(Arial_Black_16_ISO_8859_1);
      p = 0;
      q = 12;

      break;
    case 5:
      dmd.selectFont(Arial_Black_16);
      p = 0;
      q = 14;

    case 6:
      dmd.selectFont(BodoniMTBlack24);
      p = 0;
      q = 17;
      break;
    case 7:
      dmd.selectFont(Droid_Sans_24);
      p = 0;
      q = 19;
      break;
    case 8:
      dmd.selectFont(Comic24);
      p = 0;
      q = 22;

      break;
    case 9:
      dmd.selectFont(BigNumber);
      p = 0;
      q = 14;
      break;
    case 10:
      dmd.selectFont(Arial_38b);
      p = 0;
      q = 28;
      break;
    case 11:
      dmd.selectFont(Arial_14);
      p = 0;
      q = 11;
      break;
    case 12:
      dmd.selectFont(Arial_Black21);
      p = 0;
      q = 20;
      break;
    case 13:
      dmd.selectFont(Tahoma_32);
      p = 0;
      q = 9;
      break;
  }
}
void graphicsmode()
{
  int grap = atoi(graphics);
  switch (grap)
  {
    case 1:
      g = GRAPHICS_NORMAL;
      break;
    case 2:
      g = GRAPHICS_INVERSE;
      break;
    case 3:
      g = GRAPHICS_TOGGLE;
      break;
    case 4:
      g = GRAPHICS_OR;
      break;
    case 5:
      g = GRAPHICS_NOR;
      break;
  }
}

void switchcommands()
{
  //aws payload >>
  int ani = atoi(animation);
  int x = atoi(positionx);
  int y = atoi(positiony);
  int spd = 35;

  if (ani == 1)
  {
    dmd.clearScreen( true );
    fontmode();
    //dmd.selectFont(fn);

    dmd.drawString(x, y, Data, strlen(Data), g );
  }
  else if (ani == 2)
  {
    fontmode();
    //dmd.selectFont( fn );
    delay(200);
    dmd.drawMarquee(Data, strlen(Data), (32 * DISPLAYS_ACROSS) - 1, y);
    long start = millis();
    long timer = start;
    boolean ret = false;
    while (!ret) {
      if ((timer + 30) < millis()) {
        ret = dmd.stepSplitMarquee(y + p, y + q); // parameters are the top & bottom rows to be scrolled
        timer = millis();
        //client.loop();
      }
    }
  }
  else if (ani == 3)
  {
    dmd.clearScreen( true );
    fontmode();
    //dmd.selectFont(fn);
    dmd.drawString(x, y, Data, strlen(Data), g );
    dmd.drawBox(  0,  0, (32 * DISPLAYS_ACROSS) - 1, (16 * DISPLAYS_DOWN) - 1, g );
    delay( 2000 );
  }
  else if (ani == 4)
  {
    dmd.clearScreen( true );
    for (int a = 0 - (strlen(Data) * 6); a < 129; a++) {
      fontmode();
      //  dmd.selectFont( fn );
      dmd.drawString(a, y, Data, strlen(Data), g);
      delay(spd);
    }
    dmd.clearScreen( true );
  }
  delay(2000);
}
