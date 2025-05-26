#include "tuple.h"
#include <cmath>
#include <stdexcept>

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

Tuple Tuple::operator * (float scalar) {
    return Tuple(this->x * scalar, this->y * scalar, this->z * scalar, this->w);
}

Tuple operator + (Tuple t1, Tuple t2) {
    if (t1.isPoint() && t2.isPoint()) 
        throw std::logic_error("Can't add two points!");
    
    return Tuple(t1.x + t2.x, t1.y + t2.y, t1.z + t2.z, t1.w + t2.w);
}

Tuple operator - (Tuple t1, Tuple t2) {
    if (!t1.isPoint() && t2.isPoint()) 
        throw std::logic_error("Can't add point to a vector");
        
    return Tuple(t1.x - t2.x, t1.y - t2.y, t1.z - t2.z, t1.w - t2.w);
}