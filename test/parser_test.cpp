#include "lex.h"
#include "parser.h"
#include "expr.h"

#include <catch2/catch_test_macros.hpp>
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
  std::shared_ptr<bello::AbsExpr> l1 =
      std::make_shared<bello::Expr<bello::LiteralPackage>>(tk2);

  std::shared_ptr<bello::AbsExpr> l2 =
      std::make_shared<bello::Expr<bello::LiteralPackage>>(
          bello::LiteralPackage(tk3));

  std::shared_ptr<bello::AbsExpr> b1 =
      std::make_shared<bello::Expr<bello::BinaryPackage>>(
          bello::BinaryPackage(tk1, l1, l2));
  bello::AstPrinter printer;
  WARN(printer.print(dynamic_cast<bello::AbsExpr &>(*b1)));
}

TEST_CASE("Test parser") {
  std::string express = " a + b + c * (5 -1)";
  bello::Scanner lexer{express};
  auto & tk = lexer.scanTokens();
  REQUIRE(tk.size() > 0);
  bello::Parser parser{tk};
  bello::AbsExprPtr expr = parser.parse();
  REQUIRE(expr.get() != nullptr);
  bello::AstPrinter astPrinter;
  auto out = astPrinter.print(*expr);
  REQUIRE_FALSE(out.empty());
  WARN(out);

}
