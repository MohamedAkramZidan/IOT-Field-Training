#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi credentials
const char* ssid = "Martell";
const char* password = "MarwanMartell@04";

// LED GPIOs
const int led1 = 26;
const int led2 = 27;

// Web server on port 80
WebServer server(80);

// HTML page content
const char htmlPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 LED Control</title>
  <style>
    body { font-family: Arial; text-align: center; padding: 20px; background: #f0f0f0; }
    h2 { color: #333; }
    .btn {
      padding: 15px 30px;
      margin: 10px;
      font-size: 16px;
      border: none;
      border-radius: 5px;
      cursor: pointer;
    }
    .on { background-color: #4CAF50; color: white; }
    .off { background-color: #f44336; color: white; }
  </style>
</head>
<body>
  <h2>ESP32 LED Control</h2>
  <p><b>LED 1 (GPIO 26):</b></p>
  <button class="btn on" onclick="location.href='/led1/on'">ON</button>
  <button class="btn off" onclick="location.href='/led1/off'">OFF</button>

  <p><b>LED 2 (GPIO 27):</b></p>
  <button class="btn on" onclick="location.href='/led2/on'">ON</button>
  <button class="btn off" onclick="location.href='/led2/off'">OFF</button>
</body>
</html>
)rawliteral";

// Handler for root page
void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

// Handlers for LED1
void handleLED1On() {
  digitalWrite(led1, HIGH);
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}

void handleLED1Off() {
  digitalWrite(led1, LOW);
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}

// Handlers for LED2
void handleLED2On() {
  digitalWrite(led2, HIGH);
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}

void handleLED2Off() {
  digitalWrite(led2, LOW);
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}

void setup() {
  Serial.begin(115200);

  // Configure LED pins
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Set up web server routes
  server.on("/", handleRoot);
  server.on("/led1/on", handleLED1On);
  server.on("/led1/off", handleLED1Off);
  server.on("/led2/on", handleLED2On);
  server.on("/led2/off", handleLED2Off);

  // Start server
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}
