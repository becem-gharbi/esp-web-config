#include "WebConfig.h"

WebConfig::WebConfig(int port = 80) : _server(port)
{
}

bool WebConfig::begin()
{
    // Load configuration

    // Initialize SPIFFS
    if (!SPIFFS.begin(true))
    {
        Serial.println("[WebConfig] Failed to mount SPIFFS");
        return false;
    }

    // Setup an AP
    const String mac = WiFi.macAddress();

    if (!WiFi.softAP(mac))
    {
        Serial.println("[WebConfig] Failed to start AP");
        return false;
    }

    // Register server handlers
    _server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(200, "text/plain", "Hello, world"); });

    // Start server
    _server.begin();

    Serial.print("[WebConfig] Started on ");
    Serial.println(WiFi.softAPIP());

    return true;
}

void WebConfig::end()
{
}

void WebConfig::load()
{
}

void WebConfig::reset()
{
}
