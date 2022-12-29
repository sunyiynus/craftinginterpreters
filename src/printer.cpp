#include "printer.h"
#include "expr.h"
#include "lex.h"
#include "object.h"
#include "types.h"

using namespace bello;

bstring Printer::visit(BinaryExpr *be) {
  bstring res{"("};
  res += be->tk.literal;
  res += " " + be->left->print(*this);
  res += " " + be->right->print(*this);
  res += ")";
  return res;
}

bstring Printer::visit(UnaryExpr *ue) {
  bstring res{"("};
  res += ue->tk.literal;
  res += " " + ue->expr->print(*this);
  res += ")";
  return res;
}

bstring Printer::visit(GroupExpr *ue) {
  bstring res{"(Group"};
  res += " " + ue->expr->print(*this);
  res += ")";
  return res;
}

bstring Printer::visit(LiteralExpr *ue) {
  bstring res;
  res += ue->tk.literal;
  return res;
}


Printer::~Printer() {}