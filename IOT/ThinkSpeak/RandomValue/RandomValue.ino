/*
  Adapted from WriteSingleField Example from ThingSpeak Library (Mathworks)
  
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-thingspeak-publish-arduino/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <WiFi.h>
#include "ThingSpeak.h"


const char* ssid = "Embedded";   // your network SSID (name) 
const char* password = "1234567890@";   // your network password

WiFiClient  client;

unsigned long myChannelNumber = 2;
const char * myWriteAPIKey = "OPNPIK79UUHEW9B9";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;


float temperatureC;


void setup() {
  Serial.begin(115200);  //Initialize serial
  
  WiFi.mode(WIFI_STA);   
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak
 
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }
    
    long r1 = random(100);
 
    Serial.print("Temperature (ºC): ");
    Serial.println(r1);
        
    int x = ThingSpeak.writeField(myChannelNumber, 1, r1, myWriteAPIKey);

    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    lastTime = millis();
  }
}
