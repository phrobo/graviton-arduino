#ifndef GRAVITON_READER_H
#define GRAVITON_READER_H

#include "graviton-packet.h"

#include <Arduino.h>

#define PACKET_RINGBUF_SIZE 3
#define STREAMBUF_SIZE 32

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

  unsigned char m_streamBuf[STREAMBUF_SIZE];
  uint8_t m_bufHead;
  uint8_t m_bufTail;
  uint8_t m_curPacketBuf;
  uint8_t m_parserBufIdx;
  uint8_t m_lastPacketBuf;
  GravitonPacket m_packets[PACKET_RINGBUF_SIZE];
  ParserState m_parserState;
};

#endif // GRAVITON_READER_H
