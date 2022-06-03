#include <catch2/catch_test_macros.hpp>
#include "errorreport.h"

TEST_CASE("Testing error reporting") {
  using namespace bello;
  bello::Token tk1{"+", 1, bello::TOKEN_TYPE::PLUS};
  ErrorReport::reporter().warning(tk1,"Syntax error.");
  ErrorReport::reporter().error(tk1,"Syntax error.");
  ErrorReport::reporter().note(tk1,"Syntax error.");
}