#include "catch2/catch_message.hpp"
#include "expr.h"
#include "lex.h"
#include "parser.h"
#include "printer.h"

#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <cstdio>
#include <memory>

int add(int a, int b) { return a + b; }

TEST_CASE("test for test") { REQUIRE(add(1, 2) == 3); }

TEST_CASE("Test AbsExpr") {

  std::string express = "var i = 10; var c = 32; var d_ = i + c;";
  bello::Scanner lexer{express};
  auto &tokens = lexer.scanTokens();
  bello::Token tk1{"+", 1, bello::TOKEN_TYPE::PLUS};
  bello::Token tk2{"10", 0, bello::TOKEN_TYPE::NUMBER};
  bello::Token tk3{"32", 0, bello::TOKEN_TYPE::NUMBER};
  bello::AbsExpr::ptr l1 = bello::LiteralExpr::create(tk2);
  bello::AbsExpr::ptr l2 = bello::LiteralExpr::create(tk3);

  bello::AbsExpr::ptr b1 = bello::BinaryExpr::create(l1, l2, tk1);
  REQUIRE(b1.get() != nullptr);
  //bello::AstPrinter printer;
  bello::Printer printer;

  WARN(b1->print(printer));
}

TEST_CASE("Test parser") {
  std::string express = " a + b + c * (5 -1)";
  bello::Scanner lexer{express};
  auto &tk = lexer.scanTokens();
  REQUIRE(tk.size() > 0);
  bello::Parser parser{tk};
  bello::AbsExpr::ptr expr = parser.expression();
  REQUIRE(expr.get() != nullptr);
  bello::Printer printer;
  WARN(expr->print(printer));
}

/*

TEST_CASE("Test parser - error testing") {
  std::string express = " a + b + c * (5 -1";
  bello::Scanner lexer{express};
  auto &tk = lexer.scanTokens();
  REQUIRE(tk.size() > 0);
  bello::Parser parser{tk};
  bello::AbsExprPtr expr;
  try {
    expr = parser.expression();
  } catch (bello::SyntaxError& error) {
    WARN(error.what());
  }
  REQUIRE(expr.get() == nullptr);
}

TEST_CASE("Test parser - statement testing") {
  std::string express = " a + b + c * (5 -1);";
  bello::Scanner lexer{express};
  auto &tk = lexer.scanTokens();
  REQUIRE(tk.size() > 0);
  bello::Parser parser{tk};
  auto stmt = parser.parseStmts();
  REQUIRE(stmt.size() == 1);
}
*/