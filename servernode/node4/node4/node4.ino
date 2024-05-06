#include <ESP8266WiFi.h>
#include <WiFiClient.h>

// WiFi credentials
const char* ssid = "Ashutosh"; // Same SSID as Node 1's access point
const char* password = "password"; // Same password as Node 1's access point

const char* serverIP = "192.168.4.1"; // IP address of Node 1's access point
const int serverPort = 80;

void setup() {
  Serial.begin(115200);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Generate a random integer between 0 and 1000
    int randNum = random(1000);
    
    // Send HTTP GET request with the random value to Node 1's server
    WiFiClient client;
    if (client.connect(serverIP, serverPort)) {
      Serial.println("Connected to server");
      client.print("GET /update?message2=");
      client.print(randNum);
      client.print(" HTTP/1.1\r\n");
      client.print("Host: ");
      client.print(serverIP);
      client.print("\r\n");
      client.print("Connection: close\r\n\r\n");
      client.stop();
      Serial.print("Random value sent to server: ");
      Serial.println(randNum);
    } else {
      Serial.println("Failed to connect to server");
    }
    delay(5000); // Send the message every 5 seconds
  }
}
