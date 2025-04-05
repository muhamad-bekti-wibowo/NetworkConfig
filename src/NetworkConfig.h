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
    void handleNetworkSettingsChange(AsyncWebServerRequest *request);
    
    // Configuration properties
    bool shouldRestart = false;

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