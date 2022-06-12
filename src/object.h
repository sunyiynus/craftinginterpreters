#ifndef OBJECT_H
#define OBJECT_H
#include <memory>
#include <stdexcept>
#include <string>

#include "types.h"

namespace bello {

const bstring StringTypeStr{"String"};
const bstring NumberTypeStr{"Number"};
const bstring BooleanTypeStr{"Boolean"};
const bstring NilTypeStr{"Nil"};

struct Object {
  Object(const bstring &t);
  bstring type;

private:
  Object();
};

inline Object::Object() : type("Undefined Value Type") {}

inline Object::Object(const bstring &t) : type(t) {}

typedef std::shared_ptr<Object> ObjectPtr;

template <typename T, typename... Args>
std::shared_ptr<T> MakeObject(Args &&..._Args) {
  return std::make_shared<T>(_Args...);
}

struct Boolean : public Object {
  explicit Boolean(const bool v);

  bool value;
  std::shared_ptr<Boolean> toNumber() const;
};

inline Boolean::Boolean(const bool v) : value(v), Object("Boolean") {}

inline std::shared_ptr<Boolean> operator==(const Boolean &a, const Boolean &b) {
  return MakeObject<Boolean>(a.value == b.value);
}

struct Number : public Object {
  Number(const double v);
  double value;
};

inline std::shared_ptr<Boolean> operator==(const Number &a, const Number &b) {
  return MakeObject<Boolean>(a.value == b.value);
}

inline std::shared_ptr<Boolean> operator!=(const Number &a, const Number &b) {
  return MakeObject<Boolean>(a.value != b.value);
}

inline std::shared_ptr<Boolean> operator>=(const Number &a, const Number &b) {
  return MakeObject<Boolean>(a.value >= b.value);
}

inline std::shared_ptr<Boolean> operator<=(const Number &a, const Number &b) {
  return MakeObject<Boolean>(a.value <= b.value);
}

inline std::shared_ptr<Boolean> operator>(const Number &a, const Number &b) {
  return MakeObject<Boolean>(a.value > b.value);
}

inline std::shared_ptr<Boolean> operator<(const Number &a, const Number &b) {
  return MakeObject<Boolean>(a.value < b.value);
}

inline Number::Number(const double v) : value(v), Object("Number") {}

struct String : public Object {
  explicit String(const bstring &str);
  // bwstring value;
  bstring value;
  std::shared_ptr<Number> toNumber() const;
};

inline String::String(const bstring &str) : value(str), Object("String") {}

inline std::shared_ptr<Boolean> operator>=(const String &a, const String &b) {
  return MakeObject<Boolean>(a.value >= b.value);
}

inline std::shared_ptr<Boolean> operator<=(const String &a, const String &b) {
  return MakeObject<Boolean>(a.value <= b.value);
}

inline std::shared_ptr<Boolean> operator==(const String &a, const String &b) {
  return MakeObject<Boolean>(a.value == b.value);
}

inline std::shared_ptr<Boolean> operator!=(const String &a, const String &b) {
  return MakeObject<Boolean>(a.value != b.value);
}

inline std::shared_ptr<Boolean> operator>(const String &a, const String &b) {
  return MakeObject<Boolean>(a.value > b.value);
}

inline std::shared_ptr<Boolean> operator<(const String &a, const String &b) {
  return MakeObject<Boolean>(a.value < b.value);
}

inline std::shared_ptr<Number> String::toNumber() const {
  double val = 0;
  try {
    val = std::stod(value);
  } catch (std::invalid_argument &ina) {
    return nullptr;
  } catch (std::out_of_range &oor) {
    return nullptr;
  }
  return MakeObject<Number>(val);
}

struct Nil : public Object {
  Nil(void *v = nullptr);
  void *value;
};

inline Nil::Nil(void *v) : value(v), Object("Nil") {}

} // namespace bello

#endif // !OBJECT_H
