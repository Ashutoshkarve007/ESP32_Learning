#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>

// WiFi access point parameters
const char* apSSID = "Ashutosh";
const char* apPassword = "password";

ESP8266WebServer server(80);

String message0 = "M";
String message1 = "M1";
String message2 = "M2";
String message3 = "M3";

const char HTML_PAGE[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <style>
    body {
      margin: 0;
      padding: 0;
      background-image: url('/Vertiv.jpg');
      background-size: contain;
      background-repeat: no-repeat;
      background-position: center;
      display: flex;
      justify-content: center;
      align-items: center;
      height: 100vh;
    }
    #image-container {
      position: relative;
      border: 5px solid black; /* Add border around the image */
    }
    .message {
      background-color: rgba(255, 255, 255, 0.7); /* Semi-transparent white background */
      padding: 2px;
      font-size: 24px;
      text-align: center;
      position: absolute;
    }
    .message0 {
      top: 174px; /* Adjust the top position of message0 */
      left: 408px; /* Adjust the left position of message0 */
    }
    .message1 {
      top: 483px; /* Adjust the top position of message1 */
      left: 314px; /* Adjust the left position of message1 */
    }
    .message2 {
      bottom: 160px; /* Adjust the bottom position of message2 */
      left: 581px; /* Adjust the left position of message2 */
    }
    .message3 {
      bottom: 160px; /* Adjust the bottom position of message3 */
      right: 313px; /* Adjust the right position of message3 */
    }
  </style>
</head>
<body>
  <div id="image-container">
    <img id="image" src="/Vertiv.jpg" alt="Image">
    <div class="message message0">%MESSAGE0%</div>
    <div class="message message1">%MESSAGE1%</div>
    <div class="message message2">%MESSAGE2%</div>
    <div class="message message3">%MESSAGE3%</div>
  </div>
  <script>
    function updateMessages() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          var messages = this.responseText.split("\n");
          document.querySelector('.message0').innerText = messages[0];
          document.querySelector('.message1').innerText = messages[1];
          document.querySelector('.message2').innerText = messages[2];
          document.querySelector('.message3').innerText = messages[3];
        }
      };
      xhttp.open("GET", "/message", true);
      xhttp.send();
    }
    setInterval(updateMessages, 1000); // Update messages every 1 second
  </script>
</body>
</html>
)=====";

void handleRoot() {
  String html = FPSTR(HTML_PAGE);
  html.replace("%MESSAGE0%", message0);
  html.replace("%MESSAGE1%", message1);
  html.replace("%MESSAGE2%", message2);
  html.replace("%MESSAGE3%", message3);
  server.send(200, "text/html", html);
}

void handleMessage() {
  server.send(200, "text/plain", message0 + "\n" + message1 + "\n" + message2 + "\n" + message3);
}

void handleImage() {
  File imageFile = SPIFFS.open("/Vertiv.jpg", "r");
  if (!imageFile) {
    server.send(404, "text/plain", "File Not Found");
    return;
  }
  server.streamFile(imageFile, "Vertiv/jpeg");
  imageFile.close();
}

void handleUpdate() {
  if (server.hasArg("message0")) {
    message0 = server.arg("message0");
  }
  if (server.hasArg("message1")) {
    message1 = server.arg("message1");
  }
  if (server.hasArg("message2")) {
    message2 = server.arg("message2");
  }
  if (server.hasArg("message3")) {
    message3 = server.arg("message3");
  }
  handleRoot();
}

void setup() {
  Serial.begin(115200);

  // Initialize SPIFFS
  if (!SPIFFS.begin()) {
    Serial.println("Failed to mount file system");
    return;
  }
  // Create access point
  WiFi.mode(WIFI_AP);
  WiFi.softAP(apSSID, apPassword);

  Serial.println("Access point created");
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  // Route for root URL
  server.on("/", handleRoot);

  // Route for serving the image file
  server.on("/Vertiv.jpg", HTTP_GET, handleImage);

  // Route for getting message
  server.on("/message", HTTP_GET, handleMessage);
  
  // Route for handling update message
  server.on("/update", HTTP_GET, handleUpdate);

  // Start server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
