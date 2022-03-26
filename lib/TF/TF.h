#ifndef tf_h
#define tf_h

class TF
{
public:
  TF(unsigned char size, unsigned long (*timeFunction)());
  bool reg(unsigned long time, void (*hander)(unsigned long cTime));
  void run();
  void destroy();

private:
  unsigned long (*tf)();
  unsigned long *handlersTime;
  unsigned long *handlersTriggerAt;
  unsigned char handlerSize    = 0;
  unsigned char handlerPointer = 0;
  void (*handlers[256])(unsigned long cTime);
};

#endif