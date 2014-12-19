#include "graviton-service.h"

GravitonMethod&
GravitonService::methodByIdx(unsigned char idx) const
{
  return const_cast<GravitonMethod&>(methods[idx]);
}
