#include "catch2/catch_test_macros.hpp"
#include "lex.h"
#include "types.h"
#include <catch2/catch_all.hpp>
#include <fstream>
#include <iterator>

TEST_CASE("Normal testing") {
  std::ifstream ins{"./lox_program/lox_1.lox"};
  bstring source{std::istreambuf_iterator<char>(ins),
                 std::istreambuf_iterator<char>()};
  REQUIRE_FALSE(source.empty());

  bello::Scanner scanner{source};
  auto res = scanner.scanTokens();
}
