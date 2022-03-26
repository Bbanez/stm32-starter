#ifndef SSP_h
#define SSH_h

#include "HardwareSerial.h"
#include "SSPAddress.h"
#include "SSPConst.h"
#include "SSPPacket.h"

class SSP
{
public:
  SSP(HardwareSerial *hSerial, SSPAddress deviceAddress,
      unsigned long comm_baud, void (*onPacketReceived)(SSPPacket *packet));
  SSP(HardwareSerial *hSerial, SSPAddress deviceAddress,
      unsigned long comm_baud, void (*onPacketReceived)(SSPPacket *packet),
      bool debug);
  void send(String packetAsString);
  void send(SSPPacket *packet);
  void send(SSPPacket packet);

  bool isConnected();
  HardwareSerial *getSerial();

  void run(unsigned long t);

private:
  HardwareSerial *serial;
  SSPAddress address;
  void (*callback)(SSPPacket *packet);
  bool connected;
  bool packetStarted;
  char byteBuffer;
  String packetBuffer;
  unsigned long clearPacketBufferAt;
  bool debug;
};

#endif