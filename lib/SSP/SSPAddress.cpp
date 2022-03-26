#include "SSPAddress.h"

SSPAddress::SSPAddress() { created = false; }
SSPAddress::SSPAddress(unsigned long bytes)
{
  addr    = bytes;
  created = true;
}
SSPAddress::SSPAddress(unsigned char b1, unsigned char b2)
{
  addr = (b1 << 8);
  addr += b2;
  created = true;
}
void SSPAddress::put(unsigned char *address)
{
  address[0] = (addr >> 8) & 0xFF;
  address[1] = addr & 0xFF;
}
unsigned long SSPAddress::get() { return addr; }
unsigned char SSPAddress::get(unsigned char bytePosition)
{
  switch (bytePosition) {
    case 0: {
      return ((addr) >> 8);
    }
    case 1: {
      return (addr & 0xFF);
    }
    default: {
      return 0;
    }
  }
}
void SSPAddress::set(unsigned char b1, unsigned char b2)
{
  addr = (b1 << 8);
  addr += b2;
  created = true;
}
void SSPAddress::setByPosition(unsigned char bytePosition, unsigned char value)
{
  switch (bytePosition) {
    case 0: {
      addr = addr & 0x00FF;
      addr += (value << 8) & 0xFF00;
    } break;
    case 1: {
      addr = addr & 0xFF00;
      addr += value;
    } break;
  }
}
void SSPAddress::set(unsigned long address)
{
  addr    = address;
  created = true;
}
bool SSPAddress::isSet() { return created; }
String SSPAddress::toString()
{
  String s = "";
  s += get(0);
  s += ".";
  s += get(1);
  return s;
}