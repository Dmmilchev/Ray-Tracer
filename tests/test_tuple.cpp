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
    REQUIRE(floatEqual(point2.w, 2));
}

TEST_CASE("Tuple scalar division work", "[tuple]") {
    Tuple point1 = Tuple::point(1, 2, 3);
    Tuple point2 = point1 / 2;

    REQUIRE(floatEqual(point2.x, 0.5));
    REQUIRE(floatEqual(point2.y, 1));
    REQUIRE(floatEqual(point2.z, 1.5));
    REQUIRE(floatEqual(point2.w, 0.5));
}

TEST_CASE("Tuple unary minus work", "[tuple]") {
    Tuple a = Tuple::vector(-1, 2, -3);
    Tuple b = -a;

    REQUIRE(floatEqual(b.x, -a.x));
    REQUIRE(floatEqual(b.y, -a.y));
    REQUIRE(floatEqual(b.z, -a.z));
    REQUIRE(!b.isPoint());
}

TEST_CASE("Tuple magnitude work", "[tuple]") {
    REQUIRE(floatEqual(Tuple::vector(0, 3, 4).magnitude(), 5));
    REQUIRE(floatEqual(Tuple::vector(1, 0, 0).magnitude(), 1));
    REQUIRE(floatEqual(Tuple::vector(0, 1, 0).magnitude(), 1));
    REQUIRE(floatEqual(Tuple::vector(0, 0, 1).magnitude(), 1));
    REQUIRE(floatEqual(Tuple::vector(1, 2, 3).magnitude(), sqrt(14)));

    REQUIRE_THROWS_AS(Tuple::point(1, 2, 3).magnitude(), std::logic_error);
}

TEST_CASE("Tuple equals work", "t") {
    Tuple p1 = Tuple::point(1, 2, 3);
    Tuple p2 = Tuple::point(1, 2, 3);
    REQUIRE(p1 == p2);

    Tuple v1 = Tuple::vector(1, 2, 3);
    Tuple v2 = Tuple::vector(1, 2, 3);
    REQUIRE(v1 == v2);
}

TEST_CASE("Vector normalize", "Tuple") {
    Tuple v = Tuple::vector(1, 2, 3).normalize();
    REQUIRE(floatEqual(v.x, 0.26726));
    REQUIRE(floatEqual(v.y, 0.53452));
    REQUIRE(floatEqual(v.z, 0.80178));

    REQUIRE_THROWS_AS(Tuple::point(1, 2, 3).normalize(), std::logic_error);
}

TEST_CASE("Vector product", "Tuple") {
    Tuple v1 = Tuple::vector(1, 2, 3);
    Tuple v2 = Tuple::vector(0.5, 0.5, 0.5);
    float d = dot(v1, v2);
    REQUIRE(floatEqual(d, 3));

    Tuple p = Tuple::point(1, 2, 3);
    REQUIRE_THROWS_AS(dot(p, v1), std::logic_error);
    REQUIRE_THROWS_AS(dot(v2, p), std::logic_error);
}

TEST_CASE("Vector cross product", "[Tuple]") {
    Tuple a = Tuple::vector(1, 2, 3);
    Tuple b = Tuple::vector(2, 3, 4);

    Tuple c1 = cross(a, b);
    REQUIRE(floatEqual(c1.x, -1));
    REQUIRE(floatEqual(c1.y, 2));
    REQUIRE(floatEqual(c1.z, -1));

    Tuple c2 = cross(b, a);
    REQUIRE(floatEqual(c2.x, 1));
    REQUIRE(floatEqual(c2.y, -2));
    REQUIRE(floatEqual(c2.z, 1));
}