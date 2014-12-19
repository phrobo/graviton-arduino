#ifndef GRAVITON_STREAM_READER_H
#define GRAVITON_STREAM_READER_H

#include "graviton-reader.h"

class Stream;
class GravitonPacket;
class GravitonVariant;

class GravitonStreamReader : public GravitonReader {
public:
  GravitonStreamReader (Stream& s);
  void serialEvent();
  void reply(const GravitonPacket& pkt, GravitonVariant* ret);

private:
  Stream& m_stream;
};

#endif // GRAVITON_STREAM_READER_H
