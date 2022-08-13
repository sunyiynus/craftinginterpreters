#include "printer.h"
#include "expr.h"
#include "lex.h"
#include "object.h"
#include "types.h"

using namespace bello;

bstring Printer::print(BinaryExpr *be) {
  bstring res{"("};
  res += be->tk.literal;
  res += " " + be->left->print(*this);
  res += " " + be->right->print(*this);
  res += ")";
  return res;
}

bstring Printer::print(UnaryExpr *ue) {
  bstring res{"("};
  res += ue->tk.literal;
  res += " " + ue->expr->print(*this);
  res += ")";
  return res;
}

bstring Printer::print(GroupExpr *ue) {
  bstring res{"(Group"};
  res += " " + ue->expr->print(*this);
  res += ")";
  return res;
}

bstring Printer::print(LiteralExpr *ue) {
  bstring res;
  res += ue->tk.literal;
  return res;
}

Object::ptr Printer::evaluate(BinaryExpr *be) { return nullptr; }

Object::ptr Printer::evaluate(UnaryExpr *be) { return nullptr; }

Object::ptr Printer::evaluate(GroupExpr *be) { return nullptr; }

Object::ptr Printer::evaluate(LiteralExpr *be) { return nullptr; }

Printer::~Printer() {}