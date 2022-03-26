#include "SSP.h"

SSP::SSP(HardwareSerial *hSerial, SSPAddress deviceAddress,
         unsigned long comm_baud, void (*onPacketReceived)(SSPPacket *packet))
{
  serial  = hSerial;
  address = deviceAddress;
  serial->begin(comm_baud);
  while (!serial)
    ;
  callback            = onPacketReceived;
  connected           = false;
  packetStarted       = false;
  byteBuffer          = 0;
  packetBuffer        = "";
  clearPacketBufferAt = 0;
  debug               = false;
}

SSP::SSP(HardwareSerial *hSerial, SSPAddress deviceAddress,
         unsigned long comm_baud, void (*onPacketReceived)(SSPPacket *packet),
         bool _debug)
{
  serial  = hSerial;
  address = deviceAddress;
  serial->begin(comm_baud);
  while (!serial)
    ;
  callback            = onPacketReceived;
  connected           = false;
  packetStarted       = false;
  byteBuffer          = 0;
  packetBuffer        = "";
  clearPacketBufferAt = 0;
  debug               = _debug;
}

void SSP::send(String packetAsString) { serial->print(packetAsString); }

void SSP::send(SSPPacket *packet)
{
  packet->setFrom(address);
  serial->print(packet->toString());
}

void SSP::send(SSPPacket packet)
{
  packet.setFrom(address);
  serial->print(packet.toString());
}

bool SSP::isConnected() { return connected; }

HardwareSerial *SSP::getSerial() { return serial; }

void SSP::run(unsigned long t)
{
  if (serial->available()) {
    while (serial->available()) {
      byteBuffer = (char)serial->read();
      if (packetStarted) {
        switch (byteBuffer) {
          case SSP_END_BYTE: {
            packetStarted      = false;
            SSPPacket packet   = SSPPacket();
            String buildResult = packet.buildDebug(packetBuffer);
            if (buildResult.equals("")) {
              if (packet.getTo().get() == address.get()) {
                callback(&packet);
              }
            } else {
              packet.setTo(packet.getFrom());
              packet.setFrom(address);
              packet.setDataType(SSP_PACKET_DATA_TYPE_STRING);
              packet.setMessage(buildResult);
              send(packet);
            }
            packetBuffer = "";
          } break;
          default: {
            packetBuffer += char(byteBuffer);
          }
        }
      } else {
        if (byteBuffer == SSP_START_BYTE) {
          packetBuffer        = "";
          packetStarted       = true;
          clearPacketBufferAt = t + 2000;
        }
      }
    }
  } else if (packetStarted && clearPacketBufferAt < t) {
    packetStarted = false;
    packetBuffer  = "";
  }
}
