#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "tuple.h"
#include <cmath>

TEST_CASE("Tuple factory methods work", "[tuple]") {
    Tuple vector = Tuple::vector(1, 2, 3);
    Tuple point = Tuple::point(2, 3, 4);

    REQUIRE(!vector.isPoint());
    REQUIRE(point.isPoint());

    REQUIRE(std::fabs(vector.w) < 1e-5);
    REQUIRE(std::fabs(point.w - 1) < 1e-5);
}
