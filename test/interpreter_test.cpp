#include <catch2/catch_test_macros.hpp>

#include "catch2/catch_message.hpp"
#include "interpreter.h"
#include "expr.h"
#include "lex.h"
#include "object.h"
#include "parser.h"
#include <string>

TEST_CASE("Interpreter testing - normal") {
  std::string express = " 1 + 2 + 3 * (5 -1)";
  bello::Scanner lexer{express};
  auto &tk = lexer.scanTokens();
  REQUIRE(tk.size() > 0);
  bello::Parser parser{tk};
  bello::AbsExprPtr expr = parser.parse();
  REQUIRE(expr.get() != nullptr);
  bello::AstPrinter astPrinter;
  auto out = astPrinter.print(*expr);
  REQUIRE_FALSE(out.empty());
  WARN(out);
  bello::Interpreter interpreter;
  auto res = interpreter.interpret(*expr.get());
  REQUIRE(res->type ==  bello::NumberTypeStr);
  auto origResPtr = static_cast<const bello::Number*>(res.get());
  REQUIRE(origResPtr->value == 15);
  WARN(origResPtr->value);
}