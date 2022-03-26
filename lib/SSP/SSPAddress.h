#ifndef SSPAddress_h
#define SSPAddress_h

#include "WString.h"

class SSPAddress
{
public:
  SSPAddress();
  SSPAddress(unsigned long bytes);
  SSPAddress(unsigned char b1, unsigned char b2);

  void put(unsigned char *address);
  unsigned long get();
  unsigned char get(unsigned char bytePosition);

  void set(unsigned char b1, unsigned char b2);
  void setByPosition(unsigned char bytePosition, unsigned char value);
  void set(unsigned long address);

  bool isSet();
  String toString();

private:
  unsigned int addr = 0;
  bool created      = false;
};

#endif