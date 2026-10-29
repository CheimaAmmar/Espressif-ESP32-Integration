#include <WiFi.h>
#include <ArduinoOTA.h>

// Replace these placeholders locally before uploading.
// Do not commit your real Wi-Fi credentials or OTA password to GitHub.
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
const char* OTA_PASSWORD = "CHANGE_THIS_OTA_PASSWORD";

void setup() {
  Serial.begin(115200);
  delay(500);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  ArduinoOTA.setHostname("esp32-wroom32-ota");
  ArduinoOTA.setPassword(OTA_PASSWORD);

  ArduinoOTA.onStart([]() {
    Serial.println("OTA update started");
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("\nOTA update finished");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    if (total > 0) {
      Serial.printf("OTA progress: %u%%\r", (unsigned int)(100ULL * progress / total));
    }
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("\nOTA error: %u\n", (unsigned int)error);
  });

  ArduinoOTA.begin();
  Serial.println("OTA is ready for updates over the local Wi-Fi network.");
}

void loop() {
  // Keep OTA handling in the application, including after future updates.
  ArduinoOTA.handle();
}
