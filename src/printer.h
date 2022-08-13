#ifndef PRINTER_H
#define PRINTER_H

#include "expr.h"
#include "object.h"
#include "types.h"

namespace bello {

class Printer : public VisitorBase,
                    public Visitor<BinaryExpr>,
                    public Visitor<UnaryExpr>,
                    public Visitor<GroupExpr>,
                    public Visitor<LiteralExpr> {
public:
  ~Printer();
  bstring print(BinaryExpr *be);
  bstring print(UnaryExpr *ue);
  bstring print(GroupExpr *ue);
  bstring print(LiteralExpr *ue);

  Object::ptr evaluate(BinaryExpr *be);
  Object::ptr evaluate(UnaryExpr *be);
  Object::ptr evaluate(GroupExpr *be);
  Object::ptr evaluate(LiteralExpr *be);


};

} // namespace bello
#endif // PRINTER_H