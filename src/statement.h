#ifndef STATEMENT_H
#define STATEMENT_H

#include "expr.h"
#include "lex.h"
#include "object.h"
#include "types.h"
#include <memory>

namespace bello {
class AbsStmt {
public:
  using ptr = std::shared_ptr<AbsStmt>;
};

template <typename T> class StmtVisitable : public AbsStmt {
public:
};

class PrintStmt : public StmtVisitable<PrintStmt> {
public:
  static AbsStmt::ptr create(const AbsExpr::ptr &e);
  PrintStmt(const AbsExpr::ptr &e);
  using StmtVisitable<PrintStmt>::StmtVisitable;

  AbsExpr::ptr expr;
};

inline AbsStmt::ptr PrintStmt::create(const AbsExpr::ptr &e) {
  return std::make_shared<PrintStmt>(e);
}

inline PrintStmt::PrintStmt(const AbsExpr::ptr &e) : expr(e) {}

class ExprStmt : public StmtVisitable<ExprStmt> {
public:
  using StmtVisitable<ExprStmt>::StmtVisitable;
  static AbsStmt::ptr create(const AbsExpr::ptr &e);
  ExprStmt(const AbsExpr::ptr &e);

  AbsExpr::ptr expr;
};

inline AbsStmt::ptr ExprStmt::create(const AbsExpr::ptr &e) {
  return std::make_shared<ExprStmt>(e);
}

inline ExprStmt::ExprStmt(const AbsExpr::ptr &e) : expr(e) {}

} // namespace bello

#endif // STATEMENT_H
