#include "catch2/catch_message.hpp"
#include "catch2/catch_test_macros.hpp"
#include "lex.h"
#include "types.h"
#include <catch2/catch_all.hpp>
#include <fstream>
#include <iterator>

TEST_CASE("Normal testing") {
  std::string file = std::string(SOURCE_PATH) + "/test/lox_program/lox_1.lox";
  std::ifstream ins{file};
  bstring source{std::istreambuf_iterator<char>(ins),
                 std::istreambuf_iterator<char>()};
  REQUIRE_FALSE(source.empty());

  bello::Scanner scanner{source};
  auto res = scanner.scanTokens();
  REQUIRE_FALSE(res.empty());
}


TEST_CASE("Normal testing 2 ") {
  std::string file = std::string(SOURCE_PATH) + "/test/lox_program/lox_2.lox";
  std::ifstream ins{file};
  bstring source{std::istreambuf_iterator<char>(ins),
                 std::istreambuf_iterator<char>()};
  REQUIRE_FALSE(source.empty());

  bello::Scanner scanner{source};
  auto& res = scanner.scanTokens();
  REQUIRE_FALSE(res.empty());
}
