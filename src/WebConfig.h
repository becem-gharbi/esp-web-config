#ifndef WEB_CONFIG_H
#define WEB_CONFIG_H

#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include <Preferences.h>

class WebConfig
{
public:
    WebConfig(int port);
    bool begin();
    void end();
    String read(String key);
    void write(String key, String value);
    bool reset();

private:
    AsyncWebServer _server;
    Preferences _prefs;
};

#endif