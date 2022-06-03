#ifndef BELLO_SRC_PARSER_H
#define BELLO_SRC_PARSER_H
#include "lex.h"
#include "types.h"

#include <functional>
#include <math.h>
#include <memory>
#include <vector>
namespace bello {

class AbsExpr;
typedef std::shared_ptr<AbsExpr> AbsExprPtr;

class AbsVisitor;
class AbsPrinterVisitor;

class AbsExpr {
public:
  AbsExpr() = default;
  AbsExpr(AbsExpr &&) = default;
  AbsExpr(const AbsExpr &) = default;
  AbsExpr &operator=(AbsExpr &&) = default;
  AbsExpr &operator=(const AbsExpr &) = default;
  ~AbsExpr() = default;
  // virtual void accept(AbsVisitor &visitor) = 0;
  virtual bstring accept(AbsPrinterVisitor &visitor) = 0;

private:
};

class AbsPrinterVisitor {
public:
  AbsPrinterVisitor() = default;
  AbsPrinterVisitor(AbsPrinterVisitor &&) = default;
  AbsPrinterVisitor(const AbsPrinterVisitor &) = default;
  AbsPrinterVisitor &operator=(AbsPrinterVisitor &&) = default;
  AbsPrinterVisitor &operator=(const AbsPrinterVisitor &) = default;
  ~AbsPrinterVisitor() = default;
  virtual bstring visitBinaryExpr(AbsExpr &expr) = 0;
  virtual bstring visitUnaryExpr(AbsExpr &expr) = 0;
  virtual bstring visitGroupExpr(AbsExpr &expr) = 0;
  virtual bstring visitLiteralExpr(AbsExpr &expr) = 0;

private:
};

class AbsVisitor {
public:
  AbsVisitor() = default;
  AbsVisitor(AbsVisitor &&) = default;
  AbsVisitor(const AbsVisitor &) = default;
  AbsVisitor &operator=(AbsVisitor &&) = default;
  AbsVisitor &operator=(const AbsVisitor &) = default;
  ~AbsVisitor() = default;
  virtual AbsExprPtr visitBinaryExpr(AbsExpr &expr) = 0;
  virtual AbsExprPtr visitUnaryExpr(AbsExpr &expr) = 0;
  virtual AbsExprPtr visitGroupExpr(AbsExpr &expr) = 0;
  virtual AbsExprPtr visitLiteralExpr(AbsExpr &expr) = 0;

private:
};

class AstPrinter : public AbsPrinterVisitor {
public:
  AstPrinter() = default;
  AstPrinter(AstPrinter &&) = default;
  AstPrinter(const AstPrinter &) = default;
  AstPrinter &operator=(AstPrinter &&) = default;
  AstPrinter &operator=(const AstPrinter &) = default;
  ~AstPrinter() = default;

  bstring print(AbsExpr &expr);
  bstring visitBinaryExpr(AbsExpr &expr) override;
  bstring visitUnaryExpr(AbsExpr &expr) override;
  bstring visitGroupExpr(AbsExpr &expr) override;
  bstring visitLiteralExpr(AbsExpr &expr) override;

  bstring parenthsize(bstring literal,
                      std::vector<std::reference_wrapper<AbsExpr>> exprs);

private:
};

template <typename T> class Expr : public AbsExpr {
public:
  Expr() = default;
  Expr(const T &d);
  Expr(Expr &&) = default;
  Expr(const Expr &) = default;
  Expr &operator=(Expr &&) = default;
  Expr &operator=(const Expr &) = default;
  ~Expr() = default;
  bstring accept(AbsPrinterVisitor &printer) override;

  T data;

private:
};

template <typename T> inline Expr<T>::Expr(const T &d) : data(d) {}

template <typename T> inline bstring Expr<T>::accept(AbsPrinterVisitor &expr) {
  return data.acceptPrinter(*this, expr);
}

struct UnaryPackage {
  UnaryPackage(const UnaryPackage& up) = default;
  UnaryPackage(const Token &t, const std::shared_ptr<AbsExpr> expr);
  Token unaryOp;
  std::shared_ptr<AbsExpr> rightExpr;
  bstring acceptPrinter(AbsExpr &expr, AbsPrinterVisitor &printer);
};

inline UnaryPackage::UnaryPackage(const Token &t,
                                  const std::shared_ptr<AbsExpr> expr)
    : unaryOp(t), rightExpr(expr) {}

inline bstring UnaryPackage::acceptPrinter(AbsExpr &expr,
                                           AbsPrinterVisitor &printer) {
  return printer.visitUnaryExpr(expr);
}

struct BinaryPackage {
  BinaryPackage(const BinaryPackage& bp) = default;
  BinaryPackage(const Token &t, const std::shared_ptr<AbsExpr> le,
                const std::shared_ptr<AbsExpr> re);
  std::shared_ptr<AbsExpr> leftExpr;
  Token binaryOp;
  std::shared_ptr<AbsExpr> rightExpr;
  bstring acceptPrinter(AbsExpr &expr, AbsPrinterVisitor &printer);
};

inline BinaryPackage::BinaryPackage(const Token &t,
                                    const std::shared_ptr<AbsExpr> le,
                                    const std::shared_ptr<AbsExpr> re)
    : binaryOp(t), leftExpr(le), rightExpr(re) {}

inline bstring BinaryPackage::acceptPrinter(AbsExpr &expr,
                                            AbsPrinterVisitor &printer) {
  return printer.visitBinaryExpr(expr);
}

struct GroupPackage {
  GroupPackage(const std::shared_ptr<AbsExpr> expr);
  std::shared_ptr<AbsExpr> expr;
  bstring acceptPrinter(AbsExpr &expr, AbsPrinterVisitor &printer);
};

inline GroupPackage::GroupPackage(const std::shared_ptr<AbsExpr> e) : expr(e) {}

inline bstring GroupPackage::acceptPrinter(AbsExpr &expr,
                                           AbsPrinterVisitor &printer) {
  return printer.visitGroupExpr(expr);
}

struct LiteralPackage {
  LiteralPackage(const Token &t);
  Token literal;
  bstring acceptPrinter(AbsExpr &expr, AbsPrinterVisitor &printer);
};

inline LiteralPackage::LiteralPackage(const Token &t) : literal(t) {}

inline bstring LiteralPackage::acceptPrinter(AbsExpr &expr,
                                             AbsPrinterVisitor &printer) {
  return printer.visitLiteralExpr(expr);
}

} // namespace bello

#endif // BELLO_SRC_PARSER_H
