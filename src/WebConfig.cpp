#include "WebConfig.h"

WebConfig::WebConfig(bool logsEnabled)
{
    _logsEnabled = logsEnabled;
}

void WebConfig::begin()
{
    // Load configuration
    // Initialize SPIFFS
    // Setup WiFi AP
    // Register server handlers
    // Start server
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

void WebConfig::privateMethod()
{
}