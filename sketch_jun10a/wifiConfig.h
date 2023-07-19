#include <ESP8266WiFi.h>

// Replace with your network credentials
const char *ssid     = "speedy@bde0";
const char *password = "HURUFKECIL";

void initWifi() {
  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}
