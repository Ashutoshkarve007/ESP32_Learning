#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "your-ssid";
const char* password = "your-password";
const char* apiKey = "your-api-key";
const char* prompt = "What is the weather like today?";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}

void loop() {
  HTTPClient http;
  String url = "https://api.openai.com/v1/chatbot/generate";
  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + String(apiKey));
  String body = "{\"model\": \"chatbot-beta-001\", \"prompt\": \"" + String(prompt) + "\", \"max_tokens\": 256}";
  int httpCode = http.POST(body);
  if (httpCode > 0) {
    String response = http.getString();
    Serial.println(response);
  } else {
    Serial.println("Error making HTTP request");
  }
  http.end();
  delay(10000);
}
