# NetworkConfig

📡 WiFi configuration handler with EEPROM and AP fallback for ESP8266/ESP32.

## 📦 Features

- Stores SSID and Password in EEPROM
- Connects to WiFi automatically on boot
- Fallback to Access Point mode if connection fails
- Uses ESPAsyncWebServer

## 🛠 Dependencies

- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [EEPROM](https://www.arduino.cc/en/Reference/EEPROM)

## 📂 File Structure

- `NetworkConfig.h/.cpp` - Main library
- `EEPROMManager.h/.cpp` - Helper for EEPROM
- `DataParser.h/.cpp` - For parsing strings
- `Redirect.h` - Optional redirect handler

## 🚀 Example

```cpp
#include <Arduino.h>
#include <ESP8266WiFi.h>

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include <NetworkConfig.h>
#include <EEPROMManager.h>

#include "MainWebPage.h"
#include "Configuration.h"

EEPROMManager eeprom;
NetworkConfig networkConfig(eeprom);

void setup()
{
  Serial.begin(115200);
  networkConfig.begin();

  // Get the server instance
  AsyncWebServer *server = networkConfig.getServer();

  // Setup handlers
  server->on("/", HTTP_GET, [](AsyncWebServerRequest *request)
             { request->send_P(200, "text/html", MainWebPage); });

  server->on("/config", HTTP_GET, [](AsyncWebServerRequest *request)
             { request->send_P(200, "text/html", Configuration); });

  server->on("/ChangeNetworkSetting", HTTP_POST, [&](AsyncWebServerRequest *request)
             { networkConfig.handleNetworkSettingsChange(request); });
}
