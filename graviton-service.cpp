#include "graviton-service.h"

GravitonMethod&
GravitonService::methodByIdx(unsigned char idx) const
{
  return const_cast<GravitonMethod&>(methods[idx]);
}

void
do_serviceCount(unsigned char argc, const GravitonMethodArg* arg, GravitonVariant* ret)
{
  *ret = GravitonVariant ();
}

static const GravitonMethod introspectionMethods[] = {
  { "serviceCount", do_serviceCount},
};

GravitonIntrospectionService::GravitonIntrospectionService() :
  GravitonService("net.phrobo.graviton.introspection",
                  1,
                  introspectionMethods)
{}
