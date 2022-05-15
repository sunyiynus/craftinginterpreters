#include "catch2/catch_test_macros.hpp"
#include "lex.h"
#include <catch2/catch_all.hpp>
#include <fstream>

TEST_CASE("Normal testing") {
  bstring line = "";
  std::ifstream ins{"./lox_program/lox_1.lox"};
  bello::Scanner scanner;
  
  while (std::getline(ins, line)) {
      scanner.scanTokens(line);
  }
}