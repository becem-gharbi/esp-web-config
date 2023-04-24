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
               { request->send(SPIFFS, "/index.html", "text/html"); });

    _server.on("/app.css", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/app.css", "text/css"); });

    _server.on("/app.js", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/app.js", "text/javascript"); });

    _server.on("/favicon.svg", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(SPIFFS, "/favicon.svg", "image/svg+xml"); });

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
