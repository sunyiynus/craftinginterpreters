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

class AbsExpr;
typedef std::shared_ptr<AbsExpr> AbsExprPtr;


class VisitorBase;

class AbsExpr {
public:
  typedef std::shared_ptr<AbsExpr> ptr;
  AbsExpr() = default;
  AbsExpr(AbsExpr &&) = default;
  AbsExpr(const AbsExpr &) = default;
  AbsExpr &operator=(AbsExpr &&) = default;
  AbsExpr &operator=(const AbsExpr &) = default;
  ~AbsExpr() = default;

  virtual bstring print(VisitorBase &visitor) = 0;
  virtual Object::ptr evaluate(VisitorBase &visitor) = 0;

private:
};

class VisitorBase {
public:
  virtual ~VisitorBase() {}
};

template <typename Visitable> class Visitor {
public:
  virtual bstring print(Visitable *visitable) = 0;
  virtual Object::ptr evaluate(Visitable *visitable) = 0;
};

template <typename T> class Visitable : public AbsExpr {
public:
  bstring print(VisitorBase &t) override {
    if (Visitor<T> *vptr = dynamic_cast<Visitor<T> *>(&t)) {
      return vptr->print(static_cast<T *>(this));
    } else {
      assert(false);
    }
    return {};
  }

  Object::ptr evaluate(VisitorBase &t) override {
    if (Visitor<T> *vptr = dynamic_cast<Visitor<T> *>(&t)) {
      return vptr->evaluate(static_cast<T *>(this));
    } else {
      assert(false);
    }
    return {};
  }
};

class BinaryExpr;
class GroupExpr;
class UnaryExpr;
class LiteralExpr;

class BinaryExprVisitor : public Visitor<BinaryExpr> {
  using Visitor<BinaryExpr>::Visitor;
};

class GroupExprVisitor : public Visitor<GroupExpr> {
  using Visitor<GroupExpr>::Visitor;
};

class UnaryExprVisitor : public Visitor<UnaryExpr> {
  using Visitor<UnaryExpr>::Visitor;
};

class LiteralExprVisitor : public Visitor<LiteralExpr> {
  using Visitor<LiteralExpr>::Visitor;
};

class BinaryExpr : public Visitable<BinaryExpr> {
public:
  static AbsExpr::ptr create(const AbsExpr::ptr &l, const AbsExpr::ptr &r,
                             const Token &tt);
  BinaryExpr(const AbsExpr::ptr &l, const AbsExpr::ptr &r, const Token &tt);

  AbsExpr::ptr left;
  AbsExpr::ptr right;
  Token tk;
};

inline AbsExpr::ptr BinaryExpr::create(const AbsExpr::ptr &l,
                                       const AbsExpr::ptr &r, const Token &tt) {
  return std::make_shared<BinaryExpr>(l, r, tt);
}

inline BinaryExpr::BinaryExpr(const AbsExpr::ptr &l, const AbsExpr::ptr &r,
                              const Token &tt)
    : left(l), right(r), tk(tt) {}

class GroupExpr : public Visitable<GroupExpr> {
public:
  static AbsExpr::ptr create(const AbsExpr::ptr &e);
  GroupExpr(const AbsExpr::ptr &e);
  AbsExpr::ptr expr;
};

inline AbsExpr::ptr GroupExpr::create(const AbsExpr::ptr &e) {
  return std::make_shared<GroupExpr>(e);
}

inline GroupExpr::GroupExpr(const AbsExpr::ptr &e) : expr(e) {}

class UnaryExpr : public Visitable<UnaryExpr> {
public:
  static AbsExpr::ptr create(const AbsExpr::ptr &e, const Token &t);
  UnaryExpr(const AbsExpr::ptr &e, const Token &t);
  Token tk;
  AbsExpr::ptr expr;
};

inline AbsExpr::ptr UnaryExpr::create(const AbsExpr::ptr &e, const Token &t) {
  return std::make_shared<UnaryExpr>(e, t);
}

inline UnaryExpr::UnaryExpr(const AbsExpr::ptr &e, const Token &t)
    : expr(e), tk(t) {}

class LiteralExpr : public Visitable<LiteralExpr> {
public:
  static AbsExpr::ptr create(const Token &t);
  LiteralExpr(const Token &t);
  Token tk;
};

inline AbsExpr::ptr LiteralExpr::create(const Token &t) {
  return std::make_shared<LiteralExpr>(t);
}

inline LiteralExpr::LiteralExpr(const Token &t) : tk(t) {}

} // namespace bello

#endif // BELLO_SRC_PARSER_H
