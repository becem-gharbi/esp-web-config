#include "WebConfig.h"

WebConfig::WebConfig(int port = 80) : _server(port)
{
}

int WebConfig::begin()
{
    // Load configuration

    // Initialize SPIFFS

    // Setup an AP
    const String mac = WiFi.macAddress();

    if (!WiFi.softAP(mac))
    {
        return FAIL;
    }

    // Register server handlers
    _server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(200, "text/plain", "Hello, world"); });

    // Start server
    _server.begin();

    Serial.print("Web Config started on ");
    Serial.println(WiFi.softAPIP());

    return OK;
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
