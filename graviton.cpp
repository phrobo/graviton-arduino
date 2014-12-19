#include "Graviton.h"

#include <WString.h>

Graviton::Graviton(GravitonReader* reader, const GravitonService* services, unsigned char serviceCount) :
  m_reader (reader),
  m_services (services),
  m_serviceCount (serviceCount)
{
}

GravitonService&
Graviton::serviceByIdx(unsigned char idx) const
{
  return const_cast<GravitonService&>(m_services[idx]);
}

void
Graviton::callMethod(const GravitonMethodCallPayload& payload, GravitonVariant* ret)
{
  if (payload.serviceIdx < m_serviceCount) {
    const GravitonService& svc = m_services[payload.serviceIdx];
    if (payload.methodIdx < svc.methodCount) {
      return svc.methods[payload.methodIdx].func(0, 0, ret);
    }
  }
}

void
Graviton::findService(const GravitonFindServicePayload& payload, GravitonVariant* ret) const
{
  for (unsigned char i = 0; i < m_serviceCount;i++) {
    if (strcmp (payload.name, m_services[i].name) == 0) {
      *ret = GravitonVariant (i);
      return;
    }
  }

  *ret = GravitonVariant (-1);
}

void
Graviton::findMethod(const GravitonFindMethodPayload& payload, GravitonVariant* ret) const
{
  const GravitonService& svc = m_services[payload.serviceIdx];
  for (unsigned char i = 0; i < svc.methodCount; i++) {
    if (strcmp (payload.name, svc.methods[i].name) == 0) {
      *ret = GravitonVariant (i);
      return;
    }
  }
  *ret = GravitonVariant (-1);
}

void
Graviton::loop()
{
  m_reader->handleBuffer();
  if (m_reader->hasPacket()) {
    GravitonPacket& pkt = m_reader->readPacket();
    GravitonVariant reply;
    switch (pkt.type) {
      /*case GravitonPacket::PropertySet:
        setProperty (pkt.payload.propertySet);
        break;
      case GravitonPacket::PropertyGet:
        getProperty (pkt.payload.propertyGet);
        break;*/
      case GravitonPacket::FindService:
        findService (pkt.payload.findService, &reply);
        m_reader->reply (pkt, &reply);
        break;
      case GravitonPacket::FindMethod:
        findMethod (pkt.payload.findMethod, &reply);
        m_reader->reply (pkt, &reply);
        break;
      case GravitonPacket::MethodCall:
        callMethod (pkt.payload.methodCall, &reply);
        m_reader->reply (pkt, &reply);
      default:
        break;
    }
  }
}

void
do_peerCount(unsigned char argc, const GravitonMethodArg* arg, GravitonVariant* ret)
{
  *ret = GravitonVariant (0);
}

static const GravitonMethod introspectionMethods[] = {
  { "peerCount", do_peerCount},
};

const GravitonService Graviton::introspectionService = {
  "net.phrobo.graviton.introspection",
  1,
  introspectionMethods
};
