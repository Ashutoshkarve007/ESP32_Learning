/*
This code will send an HTTP request to the ChatGPT API, passing it a prompt and some other parameters, and then parse the response to extract the generated text. 
Note that you will need to include the HTTPClient and ArduinoJson libraries in your project and replace YOUR_API_KEY_HERE with your actual API key.
*/

#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* apiKey = "YOUR_API_KEY_HERE";

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Send an HTTP request to the ChatGPT API
  HTTPClient http;
  http.begin("https://api.openai.com/v1/chat/");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", String("Bearer ") + apiKey);

  // Construct the JSON payload for the request
  StaticJsonDocument<200> payload;
  payload["model"] = "chatbot";
  payload["prompt"] = "Hello, how are you today?";
  payload["max_tokens"] = 32;
  payload["stop"] = "endoftext";

  // Send the request and get the response
  int httpCode = http.POST(payload.as<String>());
  String response = http.getString();

  // Parse the response to extract the generated text
  StaticJsonDocument<500> json;
  DeserializationError error = deserializeJson(json, response);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }

  String generatedText = json["choices"][0]["text"].as<String>();
  Serial.println(generatedText);
}
