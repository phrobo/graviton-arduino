#ifndef GRAVITON_METHOD_H
#define GRAVITON_METHOD_H

#include "graviton-variant.h"

struct GravitonMethodArg {
  char name[16];
  union {
    int asInt;
    char asString[16];
  } value;
};

typedef void (*GravitonMethodFunc)(unsigned char argc, const GravitonMethodArg* argv, GravitonVariant* ret);

#ifndef GRAVITON_METHOD_NAME_MAXLEN
#define GRAVITON_METHOD_NAME_MAXLEN 16
#endif // GRAVITON_METHOD_NAME_MAXLEN

struct GravitonMethod {
  const char name[GRAVITON_METHOD_NAME_MAXLEN];
  const GravitonMethodFunc func;
};

#ifndef GRAVITON_SERVICE_NAME_MAXLEN
#define GRAVITON_SERVICE_NAME_MAXLEN 35
#endif // GRAVITON_SERVICE_NAME_MAXLEN

struct GravitonService {
  const char name[GRAVITON_SERVICE_NAME_MAXLEN];
  unsigned char methodCount;
  const GravitonMethod* methods;

  GravitonMethod& methodByIdx(unsigned char idx) const;
};

#endif // GRAVITON_METHOD_H
