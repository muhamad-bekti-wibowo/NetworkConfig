#include "NetworkConfig.h"
#include "DataParser.h"
NetworkConfig::NetworkConfig(EEPROMManager &eeprom, int eepromAddress)
    : _eeprom(eeprom), _eepromAddress(eepromAddress), _server(80)
{
}

AsyncWebServer *NetworkConfig::getServer()
{
    return &_server;
}

void NetworkConfig::begin()
{
    _eeprom.begin(512);

    WiFi.mode(WIFI_AP_STA);
    WiFi.disconnect();
    delay(100);

    int count;
    String dataNetwork[2];
    DataParser::parse(_eeprom.readString(0, 0, _eeprom.readByte(_eepromAddress)), dataNetwork, ',', count);

    if (_scanner.isSSIDAvailable(dataNetwork[0]))
    {
        WiFi.mode(WIFI_STA);
        WiFi.disconnect();
        WiFi.begin(dataNetwork[0], dataNetwork[1]);

        Serial.print("Connecting to WiFi...");
        int i = 0;
        while (WiFi.status() != WL_CONNECTED && i == 15)
        {
            i++;
            delay(500);
            Serial.print(".");
            if (i == 10)
            {
                setupAPMode();
            }
        }

        if (WiFi.status() == WL_CONNECTED)
        {
            Serial.println("\nConnected to WiFi.");
            Serial.print("IP Address: ");
            Serial.println(WiFi.localIP());
        }
    }
    else
    {
        setupAPMode();
    }

    setupServerHandlers();
    _server.begin();
}

void NetworkConfig::handleClient()
{
    if (shouldRestart)
    {
        Serial.println("Restarting ESP...");
        delay(5000);
        ESP.restart();
    }
}

String NetworkConfig::readSSID()
{
    int count;
    String dataNetwork[2];
    DataParser::parse(_eeprom.readString(0, 0, _eeprom.readByte(_eepromAddress)), dataNetwork, ',', count);
    return dataNetwork[0];
}

void NetworkConfig::setupAPMode()
{
    WiFi.softAP(apNamePrefix);
    Serial.println("\nAccess Point started. "+ apNamePrefix);
    Serial.print("AP IP Address: ");
    Serial.println(WiFi.softAPIP());
}

void NetworkConfig::setupServerHandlers()
{
    _server.onNotFound([](AsyncWebServerRequest *request)
                       {
        request->send(404, "text/plain", "[NOT FOUND DEBUG]");
        Serial.println("[NOT FOUND DEBUG] Sent 404 response."); });
}
void NetworkConfig::handleNetworkSettings(AsyncWebServerRequest *request)
{
    Serial.println("[NET CHANGE POST DEBUG] Request received for /ChangeNetworkSetting.php");
    String message = "";
    String ssid_val = "N/A";
    String pass_val = "N/A"; // Don't log real password

    if (request->hasParam("ssid", true))
    {
        ssid_val = request->getParam("ssid", true)->value();
        message = ssid_val;
        Serial.print("[NET CHANGE POST DEBUG] SSID received: ");
        Serial.println(ssid_val);
    }
    else
    {
        Serial.println("[NET CHANGE POST DEBUG] SSID parameter missing.");
    }

    if (request->hasParam("pass", true))
    {
        message += "," + request->getParam("pass", true)->value();
        pass_val = "****"; // Masking password for logging
        Serial.println("[NET CHANGE POST DEBUG] Password received (masked).");
    }
    else
    {
        Serial.println("[NET CHANGE POST DEBUG] Password parameter missing.");
    }

    if (message.length() > 0 && message.indexOf(',') != -1)
    {
        // EEPROM Write operations
        byte currentLength = _eeprom.readByte(_eepromAddress);
        Serial.print("[NET CHANGE POST DEBUG] Current EEPROM length byte: ");
        Serial.println(currentLength);
        Serial.print("[NET CHANGE POST DEBUG] Writing to EEPROM (address 0): ");
        Serial.println(message);

        _eeprom.writeString(message, 0, message.length());
        _eeprom.writeByte(_eepromAddress, message.length());

        Serial.print("[NET CHANGE POST DEBUG] New EEPROM length byte written: ");
        Serial.println(message.length());

        shouldRestart = true;
        Serial.println("[NET CHANGE POST DEBUG] Restart flag set to true.");

        String responseMsg = "SSID dan Password telah diganti dengan SSID: " + ssid_val + ", Pass: (disembunyikan)";
        request->send(200, "text/plain", responseMsg.c_str());
        Serial.println("[NET CHANGE POST DEBUG] Sent success response.");
    }
    else
    {
        Serial.println("[NET CHANGE POST DEBUG] Invalid data (SSID or Password missing). Sending error response.");
        request->send(400, "text/plain", "Parameter SSID atau Password tidak lengkap.");
    }
}
