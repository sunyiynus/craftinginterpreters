#ifndef BELLO_SRC_PARSER_H
#define BELLO_SRC_PARSER_H
#include "lex.h"
#include "object.h"
#include "types.h"

#include <cassert>
#include <functional>
#include <math.h>
#include <memory>
#include <vector>

namespace bello {

template <typename... Types> class PrintVisitor;

template <typename T> class PrintVisitor<T> {
public:
  virtual bstring visit(T *t) = 0;
};

template <typename T, typename... Types>
class PrintVisitor<T, Types...> : public PrintVisitor<Types...> {
public:
  using PrintVisitor<Types...>::visit;
  virtual bstring visit(T *t) = 0;
};

using PrinterVisitor = PrintVisitor<class BinaryExpr, class UnaryExpr,
                                    class GroupExpr, class LiteralExpr>;

template <typename... Types> class EvalVisitor;

template <typename T> class EvalVisitor<T> {
public:
  virtual Object::ptr visit(T *t) = 0;
};

template <typename T, typename... Types>
class EvalVisitor<T, Types...> : public EvalVisitor<Types...> {
public:
  using EvalVisitor<Types...>::visit;
  virtual Object::ptr visit(T *t) = 0;
};

using EvaluatorVisitor = EvalVisitor<class BinaryExpr, class UnaryExpr,
                                     class GroupExpr, class LiteralExpr>;

class AbsExpr {
public:
  typedef std::shared_ptr<AbsExpr> ptr;
  AbsExpr() = default;
  AbsExpr(AbsExpr &&) = default;
  AbsExpr(const AbsExpr &) = default;
  AbsExpr &operator=(AbsExpr &&) = default;
  AbsExpr &operator=(const AbsExpr &) = default;
  ~AbsExpr() = default;

  virtual bstring print(PrinterVisitor &visitor) = 0;
  virtual Object::ptr evaluate(EvaluatorVisitor &visitor) = 0;

private:
};

template <typename Derived> class ExprVisitable : public AbsExpr {
public:
  virtual bstring print(PrinterVisitor &visitor) {
    return visitor.visit(static_cast<Derived *>(this));
  }
  virtual Object::ptr evaluate(EvaluatorVisitor &visitor) {
    return visitor.visit(static_cast<Derived *>(this));
  }
};

class BinaryExpr : public ExprVisitable<BinaryExpr> {
public:
  using ExprVisitable<BinaryExpr>::ExprVisitable;

  static AbsExpr::ptr create(const AbsExpr::ptr &l, const AbsExpr::ptr &r,
                             const Token &tt);
  BinaryExpr(const AbsExpr::ptr &l, const AbsExpr::ptr &r, const Token &tt);

  AbsExpr::ptr left;
  AbsExpr::ptr right;
  Token tk;
};

class GroupExpr : public ExprVisitable<GroupExpr> {
public:
  using ExprVisitable<GroupExpr>::ExprVisitable;
  static AbsExpr::ptr create(const AbsExpr::ptr &e);
  GroupExpr(const AbsExpr::ptr &e);
  AbsExpr::ptr expr;
};

class UnaryExpr : public ExprVisitable<UnaryExpr> {
public:
  using ExprVisitable<UnaryExpr>::ExprVisitable;
  static AbsExpr::ptr create(const AbsExpr::ptr &e, const Token &t);
  UnaryExpr(const AbsExpr::ptr &e, const Token &t);
  Token tk;
  AbsExpr::ptr expr;
};

class LiteralExpr : public ExprVisitable<LiteralExpr> {
public:
  using ExprVisitable<LiteralExpr>::ExprVisitable;
  static AbsExpr::ptr create(const Token &t);
  LiteralExpr(const Token &t);
  Token tk;
};

inline AbsExpr::ptr BinaryExpr::create(const AbsExpr::ptr &l,
                                       const AbsExpr::ptr &r, const Token &tt) {
  return std::make_shared<BinaryExpr>(l, r, tt);
}

inline BinaryExpr::BinaryExpr(const AbsExpr::ptr &l, const AbsExpr::ptr &r,
                              const Token &tt)
    : left(l), right(r), tk(tt) {}

inline AbsExpr::ptr GroupExpr::create(const AbsExpr::ptr &e) {
  return std::make_shared<GroupExpr>(e);
}

inline GroupExpr::GroupExpr(const AbsExpr::ptr &e) : expr(e) {}

inline AbsExpr::ptr UnaryExpr::create(const AbsExpr::ptr &e, const Token &t) {
  return std::make_shared<UnaryExpr>(e, t);
}

inline UnaryExpr::UnaryExpr(const AbsExpr::ptr &e, const Token &t)
    : expr(e), tk(t) {}

inline AbsExpr::ptr LiteralExpr::create(const Token &t) {
  return std::make_shared<LiteralExpr>(t);
}

inline LiteralExpr::LiteralExpr(const Token &t) : tk(t) {}

} // namespace bello

#endif // BELLO_SRC_PARSER_H
