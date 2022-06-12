#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "expr.h"
#include "lex.h"
#include "object.h"
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

  template<typename T>
  T orithmetic(const T& a, const T& b, TOKEN_TYPE type);

  
    
protected:

private:
};

template<typename T>
T Interpreter::orithmetic(const T &a, const T &b, TOKEN_TYPE type) {
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

} // namespace bello
#endif // !INTERPRETER_H
