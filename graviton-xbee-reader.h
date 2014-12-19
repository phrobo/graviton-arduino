#ifndef GRAVITON_XBEE_READER
#define GRAVITON_XBEE_READER

#include "graviton-reader.h"
#include <XBee.h>

class GravitonXBeeReader : public GravitonReader {
public:
  GravitonXBeeReader (XBee* xbee);
  void serialEvent();
  void reply (const GravitonPacket& pkt, GravitonVariant* ret);

private:
  XBee* m_xbee;
};

#endif // GRAVITON_XBEE_READER
