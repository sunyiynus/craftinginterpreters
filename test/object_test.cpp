
#include "object.h"
#include <catch2/catch_test_macros.hpp>
using namespace bello;

TEST_CASE("Testing function MakeObject()") {
  auto p = bello::MakeObject<Number>(42);
  REQUIRE(p->value == 42);
  REQUIRE(p->type == "Number");
}


TEST_CASE("Testing function MakeObject()") {
      auto p = bello::MakeObject<Number>(42);
  REQUIRE(p->value == 42);
  REQUIRE(p->type == "Number");
}

