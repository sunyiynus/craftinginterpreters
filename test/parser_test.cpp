#include "parser.h"

#include <catch2/catch_test_macros.hpp>

int add(int a, int b) { return a + b; }

TEST_CASE("test for test") { REQUIRE(add(1, 2) == 3); }
