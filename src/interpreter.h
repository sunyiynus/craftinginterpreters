#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "expr.h"
#include "lex.h"
#include "object.h"

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
    
protected:

private:
};

} // namespace bello
#endif // !INTERPRETER_H
