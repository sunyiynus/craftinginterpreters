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
  AbsStmt() = default;
  AbsStmt(AbsStmt &&) = default;
  AbsStmt(const AbsStmt &) = default;
  AbsStmt &operator=(AbsStmt &&) = default;
  AbsStmt &operator=(const AbsStmt &) = default;
  ~AbsStmt() = default;
  virtual bstring accept(AbsPrinterVisitor &visitor) = 0;
  virtual ObjectPtr accept(AbsVisitor &visitor) = 0;

private:
};

typedef std::shared_ptr<AbsStmt> AbsStmtPtr;

class PrintStmt : public AbsStmt {
public:
  PrintStmt() = default;
  PrintStmt(PrintStmt &&) = default;
  PrintStmt(const PrintStmt &) = default;
  PrintStmt &operator=(PrintStmt &&) = default;
  PrintStmt &operator=(const PrintStmt &) = default;
  ~PrintStmt() = default;
  bstring accept(AbsPrinterVisitor &visitor) override;
  ObjectPtr accept(AbsVisitor &visitor) override;

private:
  Token print;
  AbsExprPtr expr;
  Token comma;
};

class ExprStmt : public AbsStmt {
public:
  ExprStmt() = default;
  ExprStmt(ExprStmt &&) = default;
  ExprStmt(const ExprStmt &) = default;
  ExprStmt &operator=(ExprStmt &&) = default;
  ExprStmt &operator=(const ExprStmt &) = default;
  ~ExprStmt() = default;
  bstring accept(AbsPrinterVisitor &visitor) override;
  ObjectPtr accept(AbsVisitor &visitor) override;

private:
  AbsExprPtr expr;
  Token comma;
};

} // namespace bello

#endif // STATEMENT_H
