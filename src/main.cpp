#include "Arduino.h"
#include "TF.h"
#include "SSP.h"

#define S Serial1

HardwareSerial Serial1(PA3, PA2);
unsigned char led = PC13;
bool ledState = false;

void onPacket(SSPPacket *packet)
{
  // Do something with packet
}
SSP ssp = SSP(&S, SSPAddress(1, 1), 115200, onPacket, false);

void blinkLed(unsigned long t)
{
  ledState = !ledState;
  digitalWrite(led, ledState);
  // S.write("Test\r\n");
  ssp.send(SSPPacket(SSPAddress(1, 2), 3, "Test\r\n"));
}

// void onPacket(SSPPacket *packet);
// void blinkLed(unsigned long t);

void setup()
{
  pinMode(led, OUTPUT);
  S.begin(115200);
}

void loop()
{
  TF tf = TF(2, &millis);
  tf.reg(1000, &blinkLed);

  while (1)
  {
    tf.run();
  }
}
