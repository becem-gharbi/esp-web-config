#include "WebConfig.h"

WebConfig::WebConfig(int port = 80) : _server(port)
{
}

void WebConfig::init()
{
    _prefs.begin("web-config", false);

    _username = read("username");
    _password = read("password");
    _passphrase = read("passphrase");
    _ssid = read("ssid");

    if (_username.length() == 0)
    {
        _username = "admin";
    }

    if (_password.length() == 0)
    {
        _password = "1234";
    }

    if (_ssid.length() == 0)
    {
        _ssid = WiFi.macAddress();
    }

    if (_passphrase.length() == 0)
    {
        _passphrase = "123456789";
    }
}

bool WebConfig::begin()
{
    init();

    // Initialize SPIFFS
    if (!SPIFFS.begin(true))
    {
        Serial.println("[WebConfig] Failed to mount SPIFFS");
        return false;
    }

    // Setup an AP

    if (!WiFi.softAP(_ssid, _passphrase))
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
                Serial.println(_username.c_str());
                Serial.println(_password.c_str());

                if (!request->authenticate(_username.c_str(), _password.c_str()))
                {
                    return request->requestAuthentication();
                }

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
                if (!request->authenticate(_username.c_str(), _password.c_str()))
                {
                    return request->requestAuthentication();
                }

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
    const char *_key = key.c_str();
    if (_prefs.isKey(_key))
    {
        return _prefs.getString(_key);
    }
    return "";
}

void WebConfig::write(String key, String value)
{
    _prefs.putString(key.c_str(), value);
}

bool WebConfig::reset()
{
    return _prefs.clear();
}
