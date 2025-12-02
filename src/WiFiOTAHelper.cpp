#include "WiFiOTAHelper.h"
#include <WiFi.h>

WiFiOTAHelper::WiFiOTAHelper(const char* apName, const char* apPassword, const char* hostname)
    : _apName(apName), _apPassword(apPassword), _hostname(hostname) {}

void WiFiOTAHelper::begin() {
    Serial.begin(115200);

    WiFiManager wm;
    // AutoConnect: starts AP + captive portal if no saved WiFi
    if (!wm.autoConnect(_apName, _apPassword)) {
        Serial.println("Failed to connect and hit timeout");
        ESP.restart();
    }

    Serial.println("Connected to WiFi!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    ArduinoOTA.setHostname(_hostname);

    ArduinoOTA.onStart([]() { Serial.println("OTA Start"); });
    ArduinoOTA.onEnd([]() { Serial.println("OTA End"); });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\n", (progress * 100) / total);
    });
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]\n", error);
    });

    ArduinoOTA.begin();
}

void WiFiOTAHelper::handle() {
    ArduinoOTA.handle();
}
