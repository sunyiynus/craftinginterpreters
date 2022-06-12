#include "interpreter.h"
#include "expr.h"
#include "lex.h"
#include "object.h"

#include <__functional/bind.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

using namespace bello;

ObjectPtr Interpreter::interpret(AbsExpr &expr) { return expr.accept(*this); }

ObjectPtr Interpreter::visitUnaryExpr(AbsExpr &expr) {
  auto &origExpr = dynamic_cast<Expr<UnaryPackage> &>(expr);
  auto loprand = origExpr.data.rightExpr->accept(*this);

  auto ops = [&](double res) -> ObjectPtr {
    if (origExpr.data.unaryOp.type == TOKEN_TYPE::MINUS) {
      return MakeObject<Number>(-res);
    } else if (origExpr.data.unaryOp.type == TOKEN_TYPE::NOT) {
      return MakeObject<Boolean>(res);
    }

    // there may effect many programs
  };

  if (loprand->type == NumberTypeStr) {
    auto numberObject = static_cast<const Number *>(loprand.get());
    auto res = numberObject->value;
    return ops(res);

  } else if (loprand->type == StringTypeStr) {
    auto numberObject = static_cast<const String *>(loprand.get());
    auto res = numberObject->toNumber();
    if (res.get()) {
      return ops(res->value);
    } else {
      // error??
    }
  }
}

ObjectPtr Interpreter::visitBinaryExpr(AbsExpr &expr) {
  auto &origExpr = dynamic_cast<Expr<BinaryPackage> &>(expr);
  auto loprands = origExpr.data.leftExpr->accept(*this);
  auto roprands = origExpr.data.rightExpr->accept(*this);

  auto ops =
      std::bind(&Interpreter::orithmetic<double>, this, std::placeholders::_1,
                std::placeholders::_2, origExpr.data.binaryOp.type);

  if (loprands->type == NumberTypeStr && roprands->type == NumberTypeStr) {

    auto origLOp = static_cast<const Number *>(loprands.get());
    auto origROp = static_cast<const Number *>(roprands.get());

    return MakeObject<Number>(ops(origLOp->value, origROp->value));

  } else if (loprands->type == NumberTypeStr &&
             roprands->type == StringTypeStr) {

    auto origLOp = static_cast<const Number *>(loprands.get());
    auto origROp = static_cast<const String *>(roprands.get());
    auto value = origROp->toNumber();
    if (value.get() == nullptr) {
      // TODO error;
    } else {
      return MakeObject<Number>(ops(origLOp->value, value->value));
    }
  } else if (loprands->type == StringTypeStr &&
             roprands->type == NumberTypeStr) {
    auto origLOp = static_cast<const String *>(loprands.get());
    auto origROp = static_cast<const Number *>(roprands.get());
    auto value = origLOp->toNumber();
    if (value.get() == nullptr) {
      // TODO error;
    } else {
      return MakeObject<Number>(ops(value->value, origROp->value));
    }

  } else {
    // TODO identifer operation
    // TODO more can convert to double
    // TODO error
  }
}

ObjectPtr Interpreter::visitGroupExpr(AbsExpr &expr) {
  auto &origExpr = dynamic_cast<Expr<GroupPackage> &>(expr);
  auto origObj = origExpr.data.expr->accept(*this);
  return origObj;
}

ObjectPtr Interpreter::visitLiteralExpr(AbsExpr &expr) {
  auto &origExpr = dynamic_cast<Expr<LiteralPackage> &>(expr);

  if (origExpr.data.literal.type == TOKEN_TYPE::NUMBER) {
    auto val = std::stod(origExpr.data.literal.literal);
    return MakeObject<Number>(val);

  } else if (origExpr.data.literal.type == TOKEN_TYPE::STRING) {
    return MakeObject<String>(origExpr.data.literal.literal);

  } else if (origExpr.data.literal.type == TOKEN_TYPE::NIL) {
    return MakeObject<Nil>();
  }
}
