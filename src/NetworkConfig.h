#ifndef NetworkConfig_h
#define NetworkConfig_h

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>


#include "EEPROMManager.h"
#include "WiFiScanner.h"

class NetworkConfig {
public:
    NetworkConfig(EEPROMManager& eeprom, int eepromAddress = 100);
    void begin();
    void handleClient();
    AsyncWebServer* getServer();
    
    // Network settings change handler
    void handleNetworkSettings(AsyncWebServerRequest *request);
    String readSSID();
    // Configuration properties
    bool shouldRestart = false;
    String apNamePrefix = "[CONFIG MODE]";
    void setApNamePrefix(const String& newPrefix) { apNamePrefix = newPrefix; }
private:
    EEPROMManager& _eeprom;
    int _eepromAddress;
    AsyncWebServer _server;
    WiFiScanner _scanner;
    
    void setupAPMode();
    void setupSTAAndAPMode();
    void setupServerHandlers();
};

#endif