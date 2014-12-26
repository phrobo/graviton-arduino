#ifndef GRAVITON_CORE_H
#define GRAVITON_CORE

#include "graviton-packet.h"
#include "graviton-reader.h"
#include "graviton-service.h"
#include <WString.h>

template<unsigned char serviceCount>
class GravitonCore {
public:
  GravitonCore(GravitonReader* reader, const GravitonService services[serviceCount]) :
    m_reader (reader),
    m_services (services)
  {}

  void setProperty(const GravitonPropertySetPayload& payload);

  void getProperty(const GravitonPropertyGetPayload& payload) const;

  void callMethod(const GravitonMethodCallPayload& payload, GravitonVariant* ret)
  {
    if (payload.serviceIdx < serviceCount) {
      const GravitonService& svc = m_services[payload.serviceIdx];
      if (payload.methodIdx < svc.methodCount) {
        return svc.methods[payload.methodIdx].func(0, 0, ret);
      }
    }
  }

  void findService(const GravitonFindServicePayload& payload, GravitonVariant* ret) const
  {
    for (unsigned char i = 0; i < serviceCount;i++) {
      if (strcmp (payload.name, m_services[i].name) == 0) {
        *ret = GravitonVariant (i);
        return;
      }
    }

    *ret = GravitonVariant (-1);
  }

  void findMethod(const GravitonFindMethodPayload& payload, GravitonVariant* ret) const
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

  void loop()
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

  GravitonService& serviceByIdx(unsigned char idx) const
  {
    return const_cast<GravitonService&>(m_services[idx]);
  }

private:
  GravitonReader* m_reader;
  const GravitonService* m_services;
};

#endif // GRAVITON_CORE
