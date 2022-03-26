#ifndef SSPPacket_h
#define SSPPacket_h

#include "HardwareSerial.h"
#include "SSPAddress.h"
#include "SSPConst.h"
#include "WString.h"

class SSPPacket
{
public:
  SSPPacket();
  SSPPacket(SSPAddress to, unsigned char data_type, String message);
  SSPPacket(SSPAddress from, SSPAddress to, unsigned char data_type,
            String message);
  bool build(String packetAsString);
  String buildDebug(String packetAsString);
  void clear();
  String toString();

  void setFrom(SSPAddress address);
  SSPAddress getFrom();
  void setTo(SSPAddress address);
  SSPAddress getTo();
  void setDataType(unsigned char data_type);
  unsigned char getDataType();
  void setMessage(String message);
  String getMessage();
  bool isCreated();

private:
  SSPAddress f;      // FROM
  SSPAddress t;      // TO
  unsigned char dt;  // DATA_TYPE
  String m;          // MESSAGE
  bool created;
};

#endif