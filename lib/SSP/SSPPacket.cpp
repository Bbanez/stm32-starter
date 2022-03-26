#include "SSPPacket.h"

SSPPacket::SSPPacket() { created = false; }
SSPPacket::SSPPacket(SSPAddress to, unsigned char data_type, String message)
{
  t       = to;
  dt      = data_type;
  m       = message;
  created = true;
}
SSPPacket::SSPPacket(SSPAddress from, SSPAddress to, unsigned char data_type,
                     String message)
{
  f       = from;
  t       = to;
  dt      = data_type;
  m       = message;
  created = true;
}

bool SSPPacket::build(String packetAsString)
{
  if (packetAsString.charAt(SSP_PACKET_MESSAGE_FIRST_BYTE_POS - 1) ==
      char(SSP_SPLIT_BYTE)) {
    String s = packetAsString.substring(SSP_PACKET_FROM_FIRST_BYTE_POS,
                                        SSP_PACKET_FROM_FIRST_BYTE_POS + 2);
    f.set(s.charAt(0), s.charAt(1));
    s = packetAsString.substring(SSP_PACKET_TO_FIRST_BYTE_POS,
                                 SSP_PACKET_TO_FIRST_BYTE_POS + 2);
    t.set(s.charAt(0), s.charAt(1));
    dt      = packetAsString.charAt(SSP_PACKET_DT_FIRST_BYTE_POS);
    m       = packetAsString.substring(SSP_PACKET_MESSAGE_FIRST_BYTE_POS);
    created = true;
    return true;
  }
  return false;
}
String SSPPacket::buildDebug(String packetAsString)
{
  if (packetAsString.charAt(SSP_PACKET_MESSAGE_FIRST_BYTE_POS - 1) ==
      char(SSP_SPLIT_BYTE)) {
    String s = packetAsString.substring(SSP_PACKET_FROM_FIRST_BYTE_POS,
                                        SSP_PACKET_FROM_FIRST_BYTE_POS + 2);
    f.set(s.charAt(0), s.charAt(1));
    s = packetAsString.substring(SSP_PACKET_TO_FIRST_BYTE_POS,
                                 SSP_PACKET_TO_FIRST_BYTE_POS + 2);
    t.set(s.charAt(0), s.charAt(1));
    dt      = packetAsString.charAt(SSP_PACKET_DT_FIRST_BYTE_POS);
    m       = packetAsString.substring(SSP_PACKET_MESSAGE_FIRST_BYTE_POS);
    created = true;
    return "";
  }
  String err = "";
  err += "Invalid split byte: ";
  err += (uint8_t)packetAsString.charAt(SSP_PACKET_MESSAGE_FIRST_BYTE_POS - 1);
  err += " != ";
  err += SSP_SPLIT_BYTE;
  err += "   ->   Buffer < ";
  for (unsigned int i = 0; i < packetAsString.length(); i++) {
    err += (uint8_t)packetAsString.charAt(i);
    err += " ";
  }
  return err;
}

void SSPPacket::clear()
{
  f.set(0);
  t.set(0);
  dt      = 0;
  m       = "";
  created = false;
}

String SSPPacket::toString()
{
  String s("");
  s += char(SSP_START_BYTE);
  unsigned char bytes[2];
  f.put(bytes);
  s += char(bytes[0]);
  s += char(bytes[1]);
  t.put(bytes);
  s += char(bytes[0]);
  s += char(bytes[1]);

  s += char(dt);
  s += char(SSP_SPLIT_BYTE);
  s += m;
  s += char(SSP_END_BYTE);
  return s;
}

SSPAddress SSPPacket::getFrom() { return f; }

void SSPPacket::setFrom(SSPAddress address) { f = address; }

SSPAddress SSPPacket::getTo() { return t; }

void SSPPacket::setTo(SSPAddress address) { t = address; }

unsigned char SSPPacket::getDataType() { return dt; }

void SSPPacket::setDataType(unsigned char data_type) { dt = data_type; }

String SSPPacket::getMessage() { return m; }

void SSPPacket::setMessage(String message) { m = message; }