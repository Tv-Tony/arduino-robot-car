#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "ESPap";
const char *password = "thereisnospoon";

ESP8266WebServer server(80);

const int ENA = D8;
const int IN1 = D4;
const int IN2 = D3;
const int ENB = D7;
const int IN3 = D2;
const int IN4 = D1;

void handleRoot() {
   String html = "<html><body>";
  html += "<h1>You are connected</h1>";
  html += "<form action='/control' method='get'>";
  html += "<button type='submit' name='direction' value='F'>Forward</button>";
  html += "<button type='submit' name='direction' value='B'>Backward</button>";
  html += "<button type='submit' name='direction' value='L'>Left</button>";
  html += "<button type='submit' name='direction' value='R'>Right</button>";
  html += "<button type='submit' name='direction' value='S'>Stop</button>";
  html += "</form></body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  digitalWrite(ENA, HIGH);  // Enable motor A
  digitalWrite(ENB, HIGH);  // Enable motor B
}

void loop() {
  server.handleClient();
}

void handleControl() {
  String direction = server.arg("direction");
 
  switch (direction[0]) {
    case 'F':
      moveForward();
      break;
    case 'B':
      moveBackward();
      break;
    case 'L':
      turnLeft();
      break;
    case 'R':
      turnRight();
      break;
    case 'S':
      stopMotors();
      break;
  }
 
  server.send(200, "text/plain", "OK");
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
