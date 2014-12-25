#ifndef GRAVITON_METHOD_H
#define GRAVITON_METHOD_H

#include "graviton-variant.h"

#ifndef GRAVITON_SERVICE_NAME_MAXLEN
#define GRAVITON_SERVICE_NAME_MAXLEN 35
#endif // GRAVITON_SERVICE_NAME_MAXLEN

#ifndef GRAVITON_METHOD_NAME_MAXLEN
#define GRAVITON_METHOD_NAME_MAXLEN 15
#endif // GRAVITON_METHOD_NAME_MAXLEN

#ifndef GRAVITON_ARG_NAME_MAXLEN
#define GRAVITON_ARG_NAME_MAXLEN 15
#endif // GRAVITON_ARG_NAME_MAXLEN


struct GravitonMethodArg {
  char name[GRAVITON_ARG_NAME_MAXLEN];
  GravitonVariant value;
};

typedef void (*GravitonMethodFunc)(unsigned char argc, const GravitonMethodArg* argv, GravitonVariant* ret);

struct GravitonMethod {
  GravitonMethod(const char* _name, const GravitonMethodFunc _func) :
    name(_name),
    func(_func) {}
  const char* name;
  const GravitonMethodFunc func;
};

struct GravitonService {
  GravitonService(const char* _name, unsigned char _methodCount, const GravitonMethod* _methods) :
    name(_name),
    methodCount(_methodCount),
    methods(_methods) {}
  GravitonMethod& methodByIdx(unsigned char idx) const;

  const char* name;
  unsigned char methodCount;
  const GravitonMethod* methods;
};

struct GravitonIntrospectionService : public GravitonService {
  GravitonIntrospectionService();
};

#endif // GRAVITON_METHOD_H
