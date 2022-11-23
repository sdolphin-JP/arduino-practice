#include <SoftwareSerial.h>

SoftwareSerial ProxySerial(2, 3);

void setup()
{
  Serial.begin(115200);
  ProxySerial.begin(115200);
}

void loop()
{
  if (0 != Serial.available())
  {
    uint8_t dat = Serial.read();

    Serial.write(dat);
    ProxySerial.write(dat);
  }

  if (0 != ProxySerial.available())
  {
    uint8_t dat = ProxySerial.read();
    
    Serial.write(dat);
    ProxySerial.write(dat);
  }
}
