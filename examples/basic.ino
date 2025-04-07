#include <Arduino.h>
#include <ESP8266WiFi.h>

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include <Network.h>
#include <EEPROMManager.h>

#include "MainWebPage.h"
#include "Configuration.h"

EEPROMManager eeprom;
NetworkConfig network(eeprom);

void setup()
{
    Serial.begin(115200);
    network.apNamePrefix = "Your Name AP";
    network.begin();
    // Get the server instance
    AsyncWebServer *server = network.getServer();

    // Setup handlers
    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send_P(200, "text/html", MainWebPage); });

    server->on("/config", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send_P(200, "text/html", Configuration); });

    server->on("/ChangeNetworkSetting", HTTP_POST, [&](AsyncWebServerRequest *request)
               { network.handleNetworkSettings(request); });

    Serial.println("Your SSID: " + network.readSSID());
}
void loop()
{
    network.handleClient();
}
