//   "m": "QuroLabs","g":"1","a":"4","x":"25","y":"7","f":"1"

#include <stdio.h>
#include <string.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <DMD32.h>

#define DEBUG true
#define MODE_1A


#define DISPLAYS_ACROSS 4
#define DISPLAYS_DOWN 2

#define MODEM_RXD 16
#define MODEM_TXD 17

#define UART_BAUD 115200

/*           P10 pins              */
#define PIN_DMD_nOE 22          //22       //4    // D22 active low Output Enable, setting this low lights all the LEDs in the selected rows. Can pwm it at very high frequency for brightness control.
#define PIN_DMD_A 19            //19       //13   // D19  default is 15   
#define PIN_DMD_B 21            //21       //12   // D21
#define PIN_DMD_CLK 18          //18       //18   // D18_SCK  is SPI Clock if SPI is used   R39
#define PIN_DMD_SCLK  2         //2        //14   // D02
#define PIN_DMD_R_DATA  23      //23       //23   // D23_MOSI is SPI Master Out if SPI is used

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
//#include "fonts/BigNumber.h"
//#include "fonts/DejaVuSans9.h"
//#include "fonts/DejaVuSansBold9.h"


DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

const char* Data = "";
const char* animation = "";
const char* positionx = "";
const char* positiony = "";
const char* graphics = "";
const char* fontm = "";

String from_usb = "";
const char* s = "";

byte g;
int p = 0;
int q = 0;

hw_timer_t * timer = NULL;

void IRAM_ATTR triggerScan()
{
  dmd.scanDisplayBySPI();
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

void setup()
{

  Serial.begin(UART_BAUD);
  delay(10);
  Serial1.begin(UART_BAUD, SERIAL_8N1, MODEM_RXD, MODEM_TXD);
  delay(10);
  dmd.selectFont(SystemFont5x7);
  Serial.println("Connecting to GSM_MQTT");
  dmd.drawString(2, 5, "Connecting", 10, GRAPHICS_NORMAL );
  sendData("AT+CRESET",1000,DEBUG);
  delay(20000);
  connect_mqtt();
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

void loop()
{
  usb_serial();
  //gsm_response();

   while (Serial.available() > 0)
  {
    delay(10);
    String a = Serial.readString();
    Serial.print(a);
  }
}


void connect_mqtt()
{
  sendData("AT+CSSLCFG=\"sslversion\",0,4", 1000, DEBUG);
  sendData("AT+CSSLCFG=\"authmode\",0,2", 1000, DEBUG);
  sendData("AT+CSSLCFG=\"cacert\",0,\"cacert.pem\"", 1000, DEBUG);
  sendData("AT+CSSLCFG=\"clientcert\",0,\"clientcert.pem\"", 1000, DEBUG);
  sendData("AT+CSSLCFG=\"clientkey\",0,\"clientkey.pem\"", 1000, DEBUG);
  sendData("AT+CPIN?", 1000, DEBUG);
  sendData("AT+CIPMODE=0", 1000, DEBUG);
  sendData("AT+CIPMODE", 1000, DEBUG);
  sendData("AT+NETOPEN", 1000, DEBUG);
  sendData("AT+CGACT=1", 1000, DEBUG);
  sendData("AT+CGACT?", 1000, DEBUG);
  delay(1000);
  sendData("AT+IPADDR", 1000, DEBUG);
  //dela

  sendData("AT+CMQTTSTART", 1000, DEBUG); //
  delay(1000);
  sendData("AT+CMQTTACCQ=0,\"SIMCom_client01\",1", 1500, DEBUG); //
  delay(1000);
  sendData("AT+CMQTTSSLCFG=0,0", 1000, DEBUG);
  delay(1000);
  Serial1.println("AT+CMQTTCONNECT=0,\"tcp://a39i0c3i2yvc9z-ats.iot.ap-south-1.amazonaws.com:8883\",60,1");

  delay(5000);

  sendData("AT+CMQTTSUBTOPIC=0,3,1", 2000, DEBUG);
  delay(1000);
  sendData("aws", 1000, DEBUG);
  delay(1000);
  sendData("AT+CMQTTSUB=0", 1000, DEBUG);
  delay(1000);
  sendData("AT+CMQTTTOPIC=0,3", 1000, DEBUG);
  delay(1000);
  sendData("aws", 1000, DEBUG);
  delay(1000);
  sendData("AT+CMQTTPAYLOAD=0,38", 1000, DEBUG);
  delay(1000);
  sendData("{\"message\":\"Hello from SIMCom Module\"}", 1000, DEBUG);
  delay(1000);
  sendData("AT+CMQTTPUB=0,1,60", 1000, DEBUG);

}

String sendData(String command, const int timeout, boolean debug)
{

  String response = "";
  if (command.equals("1A") || command.equals("1a"))
  {
    Serial.println();
    Serial.println("Get a 1A, input a 0x1A");

    //Serial1.write(0x1A);
    Serial1.write(26);
    Serial1.println();
    return "";
  }
  else
  {
    Serial1.println(command);
  }

  long int time = millis();
  while ((time + timeout) > millis())
  {
    while (Serial1.available())
    {
      char c = Serial1.read();
      response += c;
    }
  }
  if (debug)
  {
    Serial.print(response);
  }
  return response;
}
void usb_serial()
{
  while (Serial1.available() > 0)
  {
    Serial.write(Serial1.read());
    String a = Serial1.readString();

    if (a.indexOf("PAYLOAD") != -1)
    {
      int new1 = a.indexOf("PAYLOAD");
      String neww = a.substring(new1);
      int new2 = neww.indexOf('\n');
      String new3 = neww.substring(new2 + 1);

      // Serial.print(new3);
      StaticJsonDocument<512> doc;

      deserializeJson(doc, new3);

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
    yield();
  }
  while (Serial.available() > 0)
  {
#ifdef MODE_1A
    int c = -1;
    c = Serial.read();
    if (c != '\n' && c != '\r')
    {
      from_usb += (char)c;
    }
    else
    {
      if (!from_usb.equals(""))
      {
        sendData(from_usb, 0, DEBUG);
        from_usb = "";
      }
    }
#else
    Serial1.write(Serial.read());
    //  Serial.print(Serial1.read());
    yield();
#endif
  }
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
//    case 2:
//      dmd.selectFont(DejaVuSans9);
//      p = 0;
//      q = 9;
//      break;
//    case 3:
//      dmd.selectFont(DejaVuSansBold9);
//      p = 0;
//      q = 9;
//      break;
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
//    case 9:
//      dmd.selectFont(BigNumber);
//      p = 0;
//      q = 14;
//      break;
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
        ret = dmd.stepMarquee(y + p, y + q); // parameters are the top & bottom rows to be scrolled
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
