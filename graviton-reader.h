#ifndef GRAVITON_READER_H
#define GRAVITON_READER_H

#include "graviton-packet.h"

#define PACKET_RINGBUF_SIZE 5

class GravitonReader {
public:
  enum ParserState {
    Empty,
    FindServiceName,
    FindMethodServiceIdx,
    FindMethodName,
    MethodCallServiceIdx,
    MethodCallMethodIdx,
    Done
  };

  GravitonReader();
  void handleBuffer();
  bool hasPacket();
  GravitonPacket& readPacket();
  virtual void reply (const GravitonPacket& pkt, GravitonVariant* ret) = 0;
  ParserState parserState() const;
  void resetParser();

protected:
  void appendBuffer(unsigned char c);

private:
  void parseString(char* buf, unsigned char c, unsigned int maxSize);

  unsigned char m_streamBuf[128];
  int m_bufHead;
  int m_bufTail;
  int m_curPacketBuf;
  unsigned int m_parserBufIdx;
  int m_lastPacketBuf;
  GravitonPacket m_packets[PACKET_RINGBUF_SIZE];
  ParserState m_parserState;
};

#endif // GRAVITON_READER_H
