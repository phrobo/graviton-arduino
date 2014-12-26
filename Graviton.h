#ifndef GRAVITON_H
#define GRAVITON_H

#include "graviton-core.h"

#define GRAVITON_STATIC_INIT(reader, services, serviceCount) \
  static GravitonCore<serviceCount> Graviton (reader, services);

#endif // GRAVITON_H
