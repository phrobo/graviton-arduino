#ifndef GRAVITON_CORE_H
#define GRAVITON_CORE

#include "graviton-packet.h"
#include "graviton-reader.h"
#include "graviton-service.h"

class GravitonCore {
public:
  GravitonCore(GravitonReader* reader, const GravitonService* services, unsigned char serviceCount);

  void setProperty(const GravitonPropertySetPayload& payload);
  void getProperty(const GravitonPropertyGetPayload& payload) const;
  void callMethod(const GravitonMethodCallPayload& payload, GravitonVariant* ret);
  void findService(const GravitonFindServicePayload& payload, GravitonVariant* ret) const;
  void findMethod(const GravitonFindMethodPayload& payload, GravitonVariant* ret) const;
  void loop();

  GravitonService& serviceByIdx(unsigned char idx) const;

private:
  GravitonReader* m_reader;
  const GravitonService* m_services;
  const unsigned char m_serviceCount;
};

#endif // GRAVITON_CORE
