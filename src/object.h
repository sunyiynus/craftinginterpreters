#ifndef OBJECT_H
#define OBJECT_H
#include <memory>

#include "types.h"

namespace bello {

struct Object {
  Object(const bstring &t);
  bstring type;

private:
  Object();
};

inline Object::Object() : type("Undefined Value Type") {}

inline Object::Object(const bstring &t) : type(t) {}

typedef std::shared_ptr<Object> ObjectPtr;

template<typename T, typename... Args>
std::shared_ptr<T> MakeObject(Args&&... _Args) {
    return std::make_shared<T>(_Args...);
}

struct Number : public Object {
  Number(const double v);
  double value;
};

inline Number::Number(const double v) : value(v), Object("Number") {}

struct String : public Object {
  String(const bstring &str);
  // bwstring value;
  bstring value;
};

inline String::String(const bstring &str) : value(str), Object("String") {}

struct Boolean : public Object {
  Boolean(const bool v);
  bool value;
};

inline Boolean::Boolean(const bool v) : value(v), Object("Boolean") {}

struct Nil : public Object {
  Nil(void *v = nullptr);
  void *value;
};

inline Nil::Nil(void *v) : value(v), Object("Nil") {}

} // namespace bello

#endif // !OBJECT_H
