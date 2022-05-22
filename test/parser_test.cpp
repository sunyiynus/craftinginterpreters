#include "catch2/catch_message.hpp"
#include "lex.h"
#include "parser.h"

#include <catch2/catch_test_macros.hpp>
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
  std::shared_ptr<bello::Literal> l1 = std::make_shared<bello::Literal>(tk2);
  std::shared_ptr<bello::Literal> l2 = std::make_shared<bello::Literal>(tk3);
  std::shared_ptr<bello::Binary> binary{new bello::Binary(l1, tk1, l2)};
  bello::AstPrinter printer;
  WARN(printer.print(*binary));
}
