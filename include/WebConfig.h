#ifndef WEB_CONFIG_H
#define WEB_CONFIG_H

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <LittleFS.h>
#else
#include <WiFi.h>
#include <SPIFFS.h>
#endif

#include <Preferences.h>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>

#define DEFAULT_PASSPHRASE 123456789

class WebConfig
{
public:
    WebConfig(int port);
    bool begin();
    void end();
    String read(String key);
    void write(String key, String value);
    bool reset();
    void init();

private:
    AsyncWebServer _server;
    Preferences _prefs;
    bool _initialized;
    void _registerHandlers();
};

#endif