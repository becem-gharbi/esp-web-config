#include <Arduino.h>
#include "WebConfig.h"

WebConfig webConfig(80);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  if (webConfig.begin() == FAIL)
  {
    Serial.println("Web Config Failed");
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
}