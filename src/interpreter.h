#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "expr.h"
#include "lex.h"
#include "object.h"
#include <cmath>
#include <memory>
#include <vector>

namespace bello {

class Interpreter : public AbsVisitor {
public:
  Interpreter() = default;
  Interpreter(Interpreter &&) = default;
  Interpreter(const Interpreter &) = default;
  Interpreter &operator=(Interpreter &&) = default;
  Interpreter &operator=(const Interpreter &) = default;
  ~Interpreter() = default;
  ObjectPtr interpret(AbsExpr &expr);
  ObjectPtr visitBinaryExpr(AbsExpr &expr) override;
  ObjectPtr visitUnaryExpr(AbsExpr &expr) override;
  ObjectPtr visitGroupExpr(AbsExpr &expr) override;
  ObjectPtr visitLiteralExpr(AbsExpr &expr) override;

  template <typename T> T arithmetic(const T &a, const T &b, TOKEN_TYPE type);
  template <typename T>
  bool comparsion(const T &a, const T &b, TOKEN_TYPE type);
  std::shared_ptr<Boolean> comparsion(ObjectPtr a, ObjectPtr b,
                                      TOKEN_TYPE type);

  bool isArithmeticOps(TOKEN_TYPE type);
  bool isComparsionOps(TOKEN_TYPE type);
  bool isBinaryOps(TOKEN_TYPE type);

protected:
private:
};

template <typename T>
T Interpreter::arithmetic(const T &a, const T &b, TOKEN_TYPE type) {
  if (type == TOKEN_TYPE::PLUS) {
    return a + b;
  } else if (type == TOKEN_TYPE::MINUS) {
    return a - b;
  } else if (type == TOKEN_TYPE::STAR) {
    return a * b;
  } else if (type == TOKEN_TYPE::SLASH) {
    return a / b;
  } else {
    // TODO throw some error
    return 0;
  }
}

template <typename T>
bool Interpreter::comparsion(const T &a, const T &b, TOKEN_TYPE type) {
  if (type == TOKEN_TYPE::GREATER) {
    return (a > b);
  } else if (type == TOKEN_TYPE::GREATER_EQUAL) {
    return (a >= b);
  } else if (type == TOKEN_TYPE::LESS) {
    return (a < b);
  } else if (type == TOKEN_TYPE::LESS_EQUAL) {
    return (a <= b);
  } else if (type == TOKEN_TYPE::NOT_EQUAL) {
    return (a != b);
  } else if (type == TOKEN_TYPE::EQUAL_EQUAL) {
    return (a == b);
  } else {
    // TODO error handle
  }
}

} // namespace bello
#endif // !INTERPRETER_H
