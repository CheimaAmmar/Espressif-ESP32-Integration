#include <WiFi.h>
#include <ArduinoOTA.h>

// Example update to demonstrate OTA without changing the wiring.
// Fill in values locally; NEVER push actual credentials to GitHub.
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
const char* OTA_PASSWORD = "CHANGE_THIS_OTA_PASSWORD";
const char* FIRMWARE_VERSION = "1.1.0";

unsigned long lastReconnectAttempt = 0;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.print("Firmware version: ");
  Serial.println(FIRMWARE_VERSION);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP: ");
  Serial.println(WiFi.localIP());

  // Same hostname and password as v1: the OTA client can find the device.
  ArduinoOTA.setHostname("esp32-wroom32-ota");
  ArduinoOTA.setPassword(OTA_PASSWORD);
  ArduinoOTA.onStart([]() { Serial.println("OTA update started"); });
  ArduinoOTA.onEnd([]() { Serial.println("\nOTA update finished"); });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    if (total > 0) {
      Serial.printf("OTA progress: %u%%\r",
                    (unsigned int)(100ULL * progress / total));
    }
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("\nOTA error: %u\n", (unsigned int)error);
  });
  ArduinoOTA.begin();
  Serial.println("OTA ready (firmware v1.1.0)");
}

void loop() {
  ArduinoOTA.handle();

  // Attempt Wi-Fi recovery without blocking the OTA event loop.
  if (WiFi.status() != WL_CONNECTED &&
      millis() - lastReconnectAttempt >= 10000UL) {
    lastReconnectAttempt = millis();
    Serial.println("Wi-Fi lost; reconnecting...");
    WiFi.reconnect();
  }
}
