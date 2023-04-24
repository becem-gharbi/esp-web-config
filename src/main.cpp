#include <Arduino.h>
#include "WebConfig.h"

WebConfig webConfig(true);

void setup()
{
  // put your setup code here, to run once:
  webConfig.load();
  webConfig.begin();
}

void loop()
{
  // put your main code here, to run repeatedly:
}