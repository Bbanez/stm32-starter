#include "Arduino.h"
#include "TF.h"

unsigned char led = PC13;
bool ledState     = false;

void blinkLed(unsigned long t);

void setup()
{
  pinMode(led, OUTPUT);
  Serial1.begin(115200);
  while (!Serial1)
    ;
}

void loop()
{
  TF tf = TF(2, &millis);
  tf.reg(1000, &blinkLed);

  while (1) {
    tf.run();
  }
}

void blinkLed(unsigned long t)
{
  ledState = !ledState;
  digitalWrite(led, ledState);
  Serial1.write('Test ' + ledState);
}