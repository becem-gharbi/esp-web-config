#ifndef WEB_CONFIG_H
#define WEB_CONFIG_H

#include "WiFi.h"
#include "ESPAsyncWebServer.h"

class WebConfig
{
public:
    WebConfig(int port);
    int begin();
    void end();
    void load();
    void reset();

private:
    AsyncWebServer _server;
};

#endif