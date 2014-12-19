#ifndef GRAVITON_VARIANT_H
#define GRAVITON_VARIANT_H

struct GravitonVariant {
  GravitonVariant() :
    type (Null),
    value (nullptr) {}

  explicit GravitonVariant(const char* str) :
    type (String),
    value (str) {}

  explicit GravitonVariant(int i) :
    type(Integer),
    value(i) {}

  enum Type {
    Null,
    Integer,
    String
  };

  Type type;

  union v {
    int asInt;
    const char *asString;
    v(const char* str) : asString (str) {}
    v(int i) : asInt (i) {}
  } value;
};

#endif // GRAVTION_VARIANT_H
