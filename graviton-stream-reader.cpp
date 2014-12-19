#include "graviton-stream-reader.h"
#include <Stream.h>

GravitonStreamReader::GravitonStreamReader (Stream& s) :
  m_stream (s)
{}

void
GravitonStreamReader::serialEvent()
{
  while (m_stream.available()) {
    char c = m_stream.read();
    if (c == -1) {
      resetParser();
    } else {
      appendBuffer (c);
    }
  }
}

void
GravitonStreamReader::reply (const GravitonPacket& pkt, GravitonVariant* ret)
{
  uint8_t b = ret->type;
  m_stream.write ((uint8_t*)&b, sizeof (b));
  switch (ret->type) {
    case GravitonVariant::Null:
      break;
    case GravitonVariant::Integer:
      m_stream.write ((uint8_t*)&ret->value.asInt, sizeof (ret->value.asInt));
      break;
    case GravitonVariant::String:
      m_stream.write ((uint8_t*)ret->value.asString, strlen (ret->value.asString)+1);
      break;
  }
}
