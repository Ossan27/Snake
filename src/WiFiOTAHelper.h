#pragma once
#include <WiFiManager.h>
#include <ArduinoOTA.h>

class WiFiOTAHelper {
public:
    WiFiOTAHelper(const char* apName = "ESP32-Setup", const char* apPassword = "setup123", const char* hostname = "esp32-ota");

    void begin();
    void handle();

private:
    const char* _apName;
    const char* _apPassword;
    const char* _hostname;
};