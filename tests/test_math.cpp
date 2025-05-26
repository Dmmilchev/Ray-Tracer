#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "math.h"

TEST_CASE("Addition works", "[math]") {
    REQUIRE(add(2, 3) == 5);
    REQUIRE(add(-1, 1) == 0);
}
