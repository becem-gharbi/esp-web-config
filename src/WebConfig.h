#ifndef WEB_CONFIG_H
#define WEB_CONFIG_H

class WebConfig
{
public:
    WebConfig(bool logsEnabled = false);
    void begin();
    void end();
    void load();
    void reset();

private:
    bool _logsEnabled;
    void privateMethod();
};

#endif