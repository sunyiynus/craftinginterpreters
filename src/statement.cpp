#include "statement.h"
#include "expr.h"
#include "object.h"
#include "types.h"

using namespace bello;

bstring PrintStmt::accept(AbsPrinterVisitor &visitor) {
  bstring str{"print "};
  str += expr->accept(visitor);
  str += ";";
  return str;
}

ObjectPtr PrintStmt::accept(AbsVisitor &visitor) {}

bstring ExprStmt::accept(AbsPrinterVisitor &visitor) {
  bstring str{""};
  str += expr->accept(visitor) + ";";
  return str;
}

ObjectPtr ExprStmt::accept(AbsVisitor &visitor) {}
