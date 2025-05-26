#include "tuple.h"
#include <cmath>


Tuple::Tuple(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Tuple Tuple::vector(float x, float y, float z) {
    return Tuple(x, y, z, 0.0);
}

Tuple Tuple::point(float x, float y, float z) {
    return Tuple(x, y, z, 1.0);
}

bool Tuple::isPoint() const {
    return std::fabs(w - 1) < 1e-5;
}  
