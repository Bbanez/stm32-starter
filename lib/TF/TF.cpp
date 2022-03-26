#include "TF.h"

TF::TF(unsigned char size, unsigned long (*timeFunction)())
{
  tf                = timeFunction;
  handlerSize       = size;
  handlersTime      = new unsigned long[size];
  handlersTriggerAt = new unsigned long[size];
}
bool TF::reg(unsigned long time, void (*handler)(unsigned long cTime))
{
  if (handlerPointer < handlerSize) {
    handlersTime[handlerPointer]      = time;
    handlersTriggerAt[handlerPointer] = tf() + time;
    handlers[handlerPointer]          = handler;
    handlerPointer++;
    return true;
  }
  return false;
}
void TF::run()
{
  unsigned long time = tf();
  for (unsigned char i = 0; i < handlerPointer; i++) {
    if (time >= handlersTriggerAt[i]) {
      handlersTriggerAt[i] = time + handlersTime[i];
      (*handlers[i])(time);
    }
  }
}
void TF::destroy()
{
  delete[] handlersTime;
  delete[] handlersTriggerAt;
}
