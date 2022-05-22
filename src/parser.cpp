#include "parser.h"

using namespace bello;

bstring AstPrinter::print(AbsExpr &expr) { return expr.accept(*this); }

bstring AstPrinter::visitBinaryExpr(AbsExpr &expr) {
  Binary &bp = dynamic_cast<Binary &>(expr);
  return parenthsize(bp.operatr.literal, *bp.leftExpr, *bp.rightExpr);
}

bstring AstPrinter::visitUnaryExpr(AbsExpr &expr) {
  Unary &bp = dynamic_cast<Unary &>(expr);
  return parenthsize(bp.operatr.literal, *bp.rightExpr);
}

bstring AstPrinter::visitGroupExpr(AbsExpr &expr) {

  Group &bp = dynamic_cast<Group &>(expr);
  return parenthsize(*bp.expr);
}

bstring AstPrinter::visitLiteralExpr(AbsExpr &expr) {
  Literal &bp = dynamic_cast<Literal &>(expr);
  return bp.literal.literal;
}


bstring AstPrinter::visitExprExpr(AbsExpr &expr) {
    return bstring();
}

bstring AstPrinter::parenthsize(bstring literal, AbsExpr &lExpr,
                                AbsExpr &rExpr) {
  bstring str{"("};
  str += literal + " ";
  str += lExpr.accept(*this) + " ";
  str += rExpr.accept(*this) + ")";
  return str;
}

bstring AstPrinter::parenthsize(bstring literal, AbsExpr &expr) {
  bstring str{"("};
  str += literal + " ";
  str += expr.accept(*this) + ")";
  return str;
}

bstring AstPrinter::parenthsize(AbsExpr &expr) {
  bstring str;
  str += expr.accept(*this);
  return str;
}

bstring AstPrinter::parenthsize(bstring literal) { return literal; }

bstring AstPrinter::parenthsize(bstring literal, AbsExpr &expr, bstring lit) {
  bstring str;
  str += literal + " ";
  str += expr.accept(*this);
  str += literal + " ";
  return str;
}
