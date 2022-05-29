#include "parser.h"
#include <functional>

using namespace bello;

bstring AstPrinter::print(AbsExpr &expr) { return expr.accept(*this); }

bstring AstPrinter::visitBinaryExpr(AbsExpr &expr) {
  auto &bp = dynamic_cast<Expr<BinaryPackage> &>(expr);
  std::vector<std::reference_wrapper<AbsExpr>> exprs{*bp.data.leftExpr,
                                                     *bp.data.rightExpr};
  return parenthsize(bp.data.binaryOp.literal, exprs);
}

bstring AstPrinter::visitUnaryExpr(AbsExpr &expr) {
  auto &bp = dynamic_cast<Expr<UnaryPackage> &>(expr);
  std::vector<std::reference_wrapper<AbsExpr>> exprs{*bp.data.rightExpr};
  return parenthsize(bp.data.unaryOp.literal, exprs);
}

bstring AstPrinter::visitGroupExpr(AbsExpr &expr) {
  auto &bp = dynamic_cast<Expr<GroupPackage> &>(expr);
  std::vector<std::reference_wrapper<AbsExpr>> exprs{*bp.data.expr};
  return parenthsize("Group", exprs);
}

bstring AstPrinter::visitLiteralExpr(AbsExpr &expr) {
  auto &bp = dynamic_cast<Expr<LiteralPackage> &>(expr);
  return bp.data.literal.literal;
}

bstring
AstPrinter::parenthsize(bstring literal,
                        std::vector<std::reference_wrapper<AbsExpr>> exprs) {
  bstring str{"("};
  str += literal;
  for (auto expr : exprs) {
    str += " ";
    str += expr.get().accept(*this);
  }
  str += ")";

  return str;
}
