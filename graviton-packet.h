#ifndef GRAVITON_PACKET_H
#define GRAVITON_PACKET_H

#include "graviton-service.h"

struct GravitonMethodCallPayload {
  unsigned char serviceIdx;
  unsigned char methodIdx;
  unsigned char argv;
  GravitonMethodArg* args;
};

struct GravitonPropertySetPayload {
};

struct GravitonPropertyGetPayload {
};

struct GravitonFindServicePayload {
  char name[GRAVITON_SERVICE_NAME_MAXLEN+1];
};

struct GravitonFindMethodPayload {
  unsigned char serviceIdx;
  char name[GRAVITON_METHOD_NAME_MAXLEN];
};



struct GravitonPacket {
  GravitonPacket();

  bool valid;
  enum Type {
    FindService,
    FindMethod,
    MethodCall,
    PropertyGet,
    PropertySet
  };

  Type type;

  union {
    GravitonFindServicePayload findService;
    GravitonFindMethodPayload findMethod;
    GravitonPropertySetPayload propertySet;
    GravitonPropertyGetPayload propertyGet;
    GravitonMethodCallPayload methodCall;
  } payload;
};


#endif // GRAVITON_PACKET_H
