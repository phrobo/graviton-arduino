#include "graviton-reader.h"

GravitonReader::GravitonReader() :
  m_bufHead (0),
  m_bufTail (0),
  m_curPacketBuf (0),
  m_parserBufIdx (0),
  m_lastPacketBuf (0),
  m_parserState (Empty)
{
}

GravitonReader::ParserState
GravitonReader::parserState() const
{
  return m_parserState;
}

void
GravitonReader::parseString(char* buf, unsigned char c, unsigned int maxSize)
{
  buf[m_parserBufIdx++] = c;
  if (c == 0 || m_parserBufIdx >= maxSize) {
    m_parserState = GravitonReader::Done;
    m_parserBufIdx = 0;
  }
}

void
GravitonReader::handleBuffer()
{
  while (m_bufHead != m_bufTail) {
    unsigned char charIn = m_streamBuf[m_bufHead];
    GravitonPacket& cur = m_packets[m_curPacketBuf];
    switch (m_parserState) {
      case Empty:
        cur.type = (GravitonPacket::Type)charIn;
        switch (cur.type) {
          case GravitonPacket::FindService:
            m_parserState = FindServiceName;
            break;
          case GravitonPacket::FindMethod:
            m_parserState = FindMethodServiceIdx;
            break;
          case GravitonPacket::MethodCall:
            m_parserState = MethodCallServiceIdx;
            break;
          default:
            m_parserState = Empty;
        }
        break;
      case FindServiceName:
        parseString ((char*)&cur.payload.findService.name,
                     charIn,
                     sizeof (cur.payload.findService.name));
        break;
      case FindMethodServiceIdx:
        cur.payload.findMethod.serviceIdx = charIn;
        m_parserState = FindMethodName;
        break;
      case FindMethodName:
        parseString ((char*)&cur.payload.findMethod.name,
                     charIn,
                     sizeof (cur.payload.findMethod.name));
        break;

      case MethodCallServiceIdx:
        cur.payload.methodCall.serviceIdx = charIn;
        m_parserState = MethodCallMethodIdx;
        break;
      case MethodCallMethodIdx:
        cur.payload.methodCall.methodIdx = charIn;
        m_parserState = Done;
        break;
    }

    if (m_parserState == Done) {
      cur.valid = true;
      m_curPacketBuf++;
      m_curPacketBuf %= PACKET_RINGBUF_SIZE;
      m_parserState = Empty;
    }

    m_bufHead++;
    m_bufHead %= 128;
  }
}

void
GravitonReader::appendBuffer(unsigned char c)
{
  m_streamBuf[m_bufTail] = c;
  m_bufTail++;
  m_bufTail %= 128;
}

bool
GravitonReader::hasPacket()
{
  return m_packets[m_lastPacketBuf].valid;
}

GravitonPacket&
GravitonReader::readPacket()
{
  GravitonPacket& ret = m_packets[m_lastPacketBuf++];
  ret.valid = false;
  m_lastPacketBuf %= PACKET_RINGBUF_SIZE;
  return ret;
}

void
GravitonReader::resetParser()
{
  m_parserState = Empty;
}
