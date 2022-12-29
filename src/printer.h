#ifndef PRINTER_H
#define PRINTER_H

#include "expr.h"
#include "object.h"
#include "types.h"

namespace bello {

class Printer : public PrinterVisitor {
public:
  ~Printer();
  bstring visit(BinaryExpr *be) override;
  bstring visit(UnaryExpr *ue) override;
  bstring visit(GroupExpr *ue) override;
  bstring visit(LiteralExpr *ue) override;

};

} // namespace bello
#endif // PRINTER_H