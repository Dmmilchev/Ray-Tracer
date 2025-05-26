#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "tuple.h"
#include <cmath>
#include <stdexcept>

bool floatEqual(float a, float b) {
    return std::fabs(a - b) < 1e-5;
}

TEST_CASE("Tuple factory methods work", "[tuple]") {
    Tuple vector = Tuple::vector(1, 2, 3);
    Tuple point = Tuple::point(2, 3, 4);

    REQUIRE(!vector.isPoint());
    REQUIRE(point.isPoint());

    REQUIRE(floatEqual(vector.w, 0));
    REQUIRE(floatEqual(point.w, 1));
}

TEST_CASE("Tuple plus work (points)", "[tuple]") {
    Tuple point1 = Tuple::point(1, 2, 3);
    Tuple point2 = Tuple::point(2, 3, 5);

    REQUIRE_THROWS_AS(point1 + point2, std::logic_error);
}

TEST_CASE("Tuple plus work (point and vector)", "[tuple]") {
    Tuple point = Tuple::point(1, 2, 3);
    Tuple vector = Tuple::vector(2, 3, 5);
    Tuple point3 = point + vector;

    REQUIRE(floatEqual(point3.x, 3));
    REQUIRE(floatEqual(point3.y, 5));
    REQUIRE(floatEqual(point3.z, 8));
    REQUIRE(point3.isPoint());
}

TEST_CASE("Tuple plus work (vectors)", "[tuple]") {
    Tuple vector1 = Tuple::vector(1, 2, 3);
    Tuple vector2 = Tuple::vector(2, 3, 5);
    Tuple vector3 = vector1 + vector2;

    REQUIRE(floatEqual(vector3.x, 3));
    REQUIRE(floatEqual(vector3.y, 5));
    REQUIRE(floatEqual(vector3.z, 8));
    REQUIRE(!vector3.isPoint());
}

TEST_CASE("Tuple minus work (points)", "[tuple]") {
    Tuple point1 = Tuple::point(1, 2, 3);
    Tuple point2 = Tuple::point(2, 3, 5);
    Tuple vector = point1 - point2;

    REQUIRE(floatEqual(vector.x, -1));
    REQUIRE(floatEqual(vector.y, -1));
    REQUIRE(floatEqual(vector.z, -2));
    REQUIRE(!vector.isPoint());
}

TEST_CASE("Tuple minus work (point - vector)", "[tuple]") {
    Tuple point1 = Tuple::point(1, 2, 3);
    Tuple vector = Tuple::vector(2, 3, 5);
    Tuple point2 = point1 - vector;

    REQUIRE(floatEqual(point2.x, -1));
    REQUIRE(floatEqual(point2.y, -1));
    REQUIRE(floatEqual(point2.z, -2));
    REQUIRE(point2.isPoint());
}

TEST_CASE("Tuple minus work (vector - point)", "[tuple]") {
    Tuple point = Tuple::point(1, 2, 3);
    Tuple vector = Tuple::vector(2, 3, 5);

    REQUIRE_THROWS_AS(vector - point, std::logic_error);
}

TEST_CASE("Tuple scalar multiplication work", "[tuple]") {
    Tuple point1 = Tuple::point(1, 2, 3);
    Tuple point2 = point1 * 2;

    REQUIRE(floatEqual(point2.x, 2));
    REQUIRE(floatEqual(point2.y, 4));
    REQUIRE(floatEqual(point2.z, 6));
}

