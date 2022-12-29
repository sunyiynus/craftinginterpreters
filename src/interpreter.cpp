#include "interpreter.h"
#include "expr.h"
#include "lex.h"
#include "object.h"

#include <functional>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

using namespace bello;

Object::ptr Evaluator::visit(BinaryExpr *be) {
  Object::ptr res;
  return res;
}

Object::ptr Evaluator::visit(UnaryExpr *ue) {
  Object::ptr res;
  return res;
}

Object::ptr Evaluator::visit(GroupExpr *ue) {
  Object::ptr res;
  return res;
}

Object::ptr Evaluator::visit(LiteralExpr *ue) {
  Object::ptr res;
  return res;
}
