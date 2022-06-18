#include <array>
#include <catch2/catch_test_macros.hpp>

#include "catch2/catch_message.hpp"
#include "expr.h"
#include "interpreter.h"
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
  REQUIRE(res->type == bello::NumberTypeStr);
  auto origResPtr = static_cast<const bello::Number *>(res.get());
  REQUIRE(origResPtr->value == 15);
  WARN(origResPtr->value);
}

TEST_CASE("Interpreter testing - normal - 01") {
  std::string express = " 1 + 2 + 3 * (5 -1) / 2";
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
  REQUIRE(res->type == bello::NumberTypeStr);
  auto origResPtr = static_cast<const bello::Number *>(res.get());
  REQUIRE(origResPtr->value == 9);
  WARN(origResPtr->value);
}

TEST_CASE("Interpreter testing - normal - 02") {
  std::string express = "999*1/3";
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
  REQUIRE(res->type == bello::NumberTypeStr);
  auto origResPtr = static_cast<const bello::Number *>(res.get());
  REQUIRE(origResPtr->value == 333);
  WARN(origResPtr->value);
}

TEST_CASE("Interpreter testing - normal - 03 - comparsion") {
  std::string express = "100 == 100";
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
  REQUIRE(res->type == bello::BooleanTypeStr);
  auto origResPtr = static_cast<const bello::Boolean *>(res.get());
  REQUIRE(origResPtr->value == true);
  WARN(origResPtr->value);
}

TEST_CASE("Interpreter testing - normal - 04 - comparsion") {
  std::string express = "100 == 100 and 2 != 1";
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
  REQUIRE(res->type == bello::BooleanTypeStr);
  auto origResPtr = static_cast<const bello::Boolean *>(res.get());
  REQUIRE(origResPtr->value == true);
  WARN(origResPtr->value);
}

TEST_CASE("Interpreter testing - normal - 05 - comparsion") {
  std::string express = "(100 == 100) != (2 != 1)";
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
  //REQUIRE_FALSE(res);
  REQUIRE(res->type == bello::BooleanTypeStr);
  auto origResPtr = static_cast<const bello::Boolean *>(res.get());
  REQUIRE(origResPtr->value == false);
  WARN(origResPtr->value);
}