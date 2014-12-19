#include "graviton-xbee-reader.h"

GravitonXBeeReader::GravitonXBeeReader (XBee* xbee) :
  m_xbee (xbee)
{}

void
GravitonXBeeReader::serialEvent()
{
  m_xbee->readPacket();
  if (m_xbee->getResponse().isAvailable()) {
    if (m_xbee->getResponse().getApiId() == RX_64_RESPONSE) {
      Rx64Response rx;
      uint8_t* pktBuf;
      m_xbee->getResponse().getRx64Response (rx);
      pktBuf = rx.getData();
      for (int i = 0; i < rx.getDataLength(); i++) {
        appendBuffer (pktBuf[i]);
      }
    }
  }
}
  
void
GravitonXBeeReader::reply (const GravitonPacket& pkt, GravitonVariant* ret)
{
}
