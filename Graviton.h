#ifndef GRAVITON_H
#define GRAVITON_H

#include "graviton-core.h"

#define GRAVITON_STATIC_INIT(reader, methods, methodCount) \
  static GravitonCore Graviton (reader, methods, methodCount);

#endif // GRAVITON_H
