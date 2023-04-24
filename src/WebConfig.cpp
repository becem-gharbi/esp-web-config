#include "WebConfig.h"

WebConfig::WebConfig(int port = 80) : _server(port)
{
}

bool WebConfig::begin()
{
    _prefs.begin("web-config", false);

    // Initialize SPIFFS
    if (!SPIFFS.begin(true))
    {
        Serial.println("[WebConfig] Failed to mount SPIFFS");
        return false;
    }

    // Setup an AP
    String ssid = read("ssid");
    if (ssid.length() == 0)
    {
        ssid = WiFi.macAddress();
    }

    String passphrase = read("passphrase");
    if (passphrase.length() == 0)
    {
        passphrase = DEFAULT_PASSPHRASE;
    }

    if (!WiFi.softAP(ssid, passphrase))
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

    _server.addHandler(
        new AsyncCallbackJsonWebHandler(
            "/config/set",
            [&](AsyncWebServerRequest *request, JsonVariant &jsonVariant)
            {
                JsonObject jsonObj = jsonVariant.as<JsonObject>();

                for (JsonPair p : jsonObj)
                {
                    String key = p.key().c_str();
                    String value = p.value();
                    write(key, value);
                }

                request->send(200, "text/plain", "OK");
            }));

    _server.addHandler(
        new AsyncCallbackJsonWebHandler(
            "/config/get",
            [&](AsyncWebServerRequest *request, JsonVariant &jsonVariant)
            {
                JsonObject inputObj = jsonVariant.as<JsonObject>();

                DynamicJsonDocument doc(1024);
                JsonObject outputObj = doc.to<JsonObject>();

                for (JsonPair p : inputObj)
                {
                    String key = p.key().c_str();
                    outputObj[key] = read(key);
                }

                AsyncResponseStream *response = request->beginResponseStream("application/json");

                serializeJson(outputObj, *response);
                request->send(response);
            }));

    // Start server
    _server.begin();

    Serial.print("[WebConfig] Started on ");
    Serial.println(WiFi.softAPIP());

    return true;
}

void WebConfig::end()
{
    _server.end();
    SPIFFS.end();
    _prefs.end();
}

String WebConfig::read(String key)
{
    return _prefs.getString(key.c_str());
}

void WebConfig::write(String key, String value)
{
    _prefs.putString(key.c_str(), value);
}

bool WebConfig::reset()
{
    return _prefs.clear();
}
