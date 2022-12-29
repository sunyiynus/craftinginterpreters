#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "expr.h"
#include "lex.h"
#include "object.h"
#include <cmath>
#include <memory>
#include <vector>

namespace bello {

class Evaluator: public EvaluatorVisitor {
public:
    Object::ptr visit(BinaryExpr* expr);
    Object::ptr visit(UnaryExpr* expr);
    Object::ptr visit(LiteralExpr* expr);
    Object::ptr visit(GroupExpr* expr);
};

} // namespace bello
#endif // !INTERPRETER_H
