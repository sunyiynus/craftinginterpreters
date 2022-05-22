#ifndef BELLO_SRC_PARSER_H
#define BELLO_SRC_PARSER_H
#include "lex.h"
#include "types.h"

#include <math.h>
#include <memory>
namespace bello {

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
  virtual void accept(AbsVisitor &visitor) = 0;
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
  virtual bstring visitExprExpr(AbsExpr &expr) = 0;

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
  virtual void visitBinaryExpr(AbsExpr &expr) = 0;
  virtual void visitUnaryExpr(AbsExpr &expr) = 0;
  virtual void visitGroupExpr(AbsExpr &expr) = 0;
  virtual void visitLiteralExpr(AbsExpr &expr) = 0;

private:
};

#ifndef PARSER_TEMPLATE

class AstPrinter;

class Binary : public AbsExpr {
public:
  Binary() = default;
  Binary(std::shared_ptr<AbsExpr> le, Token &token,
         std::shared_ptr<AbsExpr> re);
  Binary(Binary &&) = default;
  Binary(const Binary &) = default;
  Binary &operator=(Binary &&) = default;
  Binary &operator=(const Binary &) = default;
  ~Binary() = default;

  void accept(AbsVisitor &visitor) override;
  bstring accept(AbsPrinterVisitor &visitor) override;

private:
  friend class AstPrinter;
  std::shared_ptr<AbsExpr> leftExpr;
  Token operatr;
  std::shared_ptr<AbsExpr> rightExpr;
};

inline Binary::Binary(std::shared_ptr<AbsExpr> le, Token &token,
                      std::shared_ptr<AbsExpr> re)
    : leftExpr(le), operatr(token), rightExpr(re) {}

inline void Binary::accept(AbsVisitor &visitor) {
  visitor.visitBinaryExpr(*this);
}

inline bstring Binary::accept(AbsPrinterVisitor &visitor) {
  return visitor.visitBinaryExpr(*this);
}

class Unary : public AbsExpr {
public:
  Unary() = default;
  Unary(Token &token, std::shared_ptr<AbsExpr> re);
  Unary(Unary &&) = default;
  Unary(const Unary &) = default;
  Unary &operator=(Unary &&) = default;
  Unary &operator=(const Unary &) = default;
  ~Unary() = default;

  void accept(AbsVisitor &visitor) override;
  bstring accept(AbsPrinterVisitor &visitor) override;

private:
  friend class AstPrinter;
  Token operatr;
  std::shared_ptr<AbsExpr> rightExpr;
};

inline Unary::Unary(Token &token, std::shared_ptr<AbsExpr> re)
    : operatr(token), rightExpr(re) {}

inline void Unary::accept(AbsVisitor &visitor) {
  visitor.visitUnaryExpr(*this);
}

inline bstring Unary::accept(AbsPrinterVisitor &visitor) {
  return visitor.visitBinaryExpr(*this);
}

class Group : public AbsExpr {
public:
  Group() = default;
  Group(const Token &lo, std::shared_ptr<AbsExpr> e, const Token &ro);
  Group(Group &&) = default;
  Group(const Group &) = default;
  Group &operator=(Group &&) = default;
  Group &operator=(const Group &) = default;
  ~Group() = default;
  bstring accept(AbsPrinterVisitor &visitor) override;

private:
  friend class AstPrinter;
  Token lOperatr;
  std::shared_ptr<AbsExpr> expr;
  Token rOperatr;
};

inline Group::Group(const Token &lo, std::shared_ptr<AbsExpr> e,
                    const Token &ro)
    : lOperatr(lo), expr(e), rOperatr(ro) {}

inline bstring Group::accept(AbsPrinterVisitor &visitor) {
  return visitor.visitGroupExpr(*this);
}

class Expr : public AbsExpr {
public:
  Expr() = default;
  Expr(std::shared_ptr<AbsExpr> e);
  Expr(Expr &&) = default;
  Expr(const Expr &) = default;
  Expr &operator=(Expr &&) = default;
  Expr &operator=(const Expr &) = default;
  ~Expr() = default;
  bstring accept(AbsPrinterVisitor &visitor) override;

private:
  friend class AstPrinter;
  std::shared_ptr<AbsExpr> expr;
};

inline Expr::Expr(std::shared_ptr<AbsExpr> e) : expr(e) {}

inline bstring Expr::accept(AbsPrinterVisitor &visitor) {
  return visitor.visitGroupExpr(*this);
}

class Literal : public AbsExpr {
public:
  Literal() = default;
  Literal(const Token &token);
  Literal(Literal &&) = default;
  Literal(const Literal &) = default;
  Literal &operator=(Literal &&) = default;
  Literal &operator=(const Literal &) = default;
  ~Literal() = default;
  void accept(AbsVisitor &visitor) override;
  bstring accept(AbsPrinterVisitor &visitor) override;

private:
  friend class AstPrinter;
  Token literal;
};

inline Literal::Literal(const Token &token) : literal(token) {}

inline void Literal::accept(AbsVisitor &visitor) {
  visitor.visitLiteralExpr(*this);
}

inline bstring Literal::accept(AbsPrinterVisitor &visitor) {
  return visitor.visitLiteralExpr(*this);
}

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
  bstring visitExprExpr(AbsExpr &expr) override;

  bstring parenthsize(bstring literal, AbsExpr &lExpr, AbsExpr &rExpr);
  bstring parenthsize(bstring literal, AbsExpr &expr);
  bstring parenthsize(AbsExpr &expr);
  bstring parenthsize(bstring literal);
  bstring parenthsize(bstring literal, AbsExpr &expr, bstring lit);

private:
};

#else // PARSER_TEMPLATE

template <typename T> class Expression : public AbsExpr {
public:
  Expression() = default;
  Expression(const T &d);
  Expression(Expression &&) = default;
  Expression(const Expression &) = default;
  Expression &operator=(Expression &&) = default;
  Expression &operator=(const Expression &) = default;
  ~Expression() = default;

private:
  T data;
};

template <typename T> inline Expression<T>::Expression(const T &d) : data(d) {}

struct Unary {
  Token unaryOp;
  std::shared_ptr<AbsExpr> rightExpr;
};

struct Binary {
  std::shared_ptr<AbsExpr> leftExpr;
  Token binaryOp;
  std::shared_ptr<AbsExpr> rightExpr;
};

struct Group {
  Token left;
  std::sharedrptr<AbsExpr> expr;
  Token right;
};

struct Expr {
  std::sharedrptr<AbsExpr> expr;
};

struct Literal {
  Token literal;
};

#endif // PARSER_TEMPLATE

} // namespace bello

#endif // BELLO_SRC_PARSER_H
