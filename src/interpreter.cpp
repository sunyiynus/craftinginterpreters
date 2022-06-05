#include "interpreter.h"
#include "expr.h"
#include "lex.h"
#include "object.h"
#include <vector>

using namespace bello;

ObjectPtr Interpreter::interpret(AbsExpr &expr) { return expr.accept(*this); }

ObjectPtr Interpreter::visitUnaryExpr(AbsExpr &expr) {
  auto &origExpr = dynamic_cast<Expr<UnaryPackage> &>(expr);
}

ObjectPtr Interpreter::visitBinaryExpr(AbsExpr &expr) {}

ObjectPtr Interpreter::visitGroupExpr(AbsExpr &expr) {}

ObjectPtr Interpreter::visitLiteralExpr(AbsExpr &expr) {
  auto &origExpr = dynamic_cast<Expr<LiteralPackage> &>(expr);

  if (origExpr.data.literal.type == TOKEN_TYPE::NUMBER) {
    return MakeObject<Number>(origExpr.data.literal.literal);

  } else if (origExpr.data.literal.type == TOKEN_TYPE::STRING) {
    return MakeObject<String>(origExpr.data.literal.literal);

  } else if (origExpr.data.literal.type == TOKEN_TYPE::NIL) {
    return MakeObject<Nil>();
  }
}
