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

Tuple Tuple::operator * (float scalar) const {
    return Tuple(x * scalar, y * scalar, z * scalar, w * scalar);
}

Tuple Tuple::operator / (float scalar) const {
    return *this * (1 / scalar);
}

Tuple Tuple::operator - () const {
    return *this * (-1);
}

float Tuple::magnitude() const {
    if (this->isPoint()) 
        throw std::logic_error("Points don't have magnitude");

    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));
}

Tuple Tuple::normalize() const {
    return *this / this->magnitude();
}

bool operator == (Tuple t1, Tuple t2) {
    return std::fabs(t1.x - t2.x) < 1e-5 ||
           std::fabs(t1.y - t2.y) < 1e-5 ||
           std::fabs(t1.z - t2.z) < 1e-5 ||
           std::fabs(t1.w - t2.w) < 1e-5;
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

float dot(Tuple t1, Tuple t2) {
    if (t1.isPoint() || t2.isPoint())  
        throw std::logic_error("Can't have dot product between points");

    return t1.x * t2.x + t1.y * t2.y + t1.z * t2.z + t1.w * t2.w; 
}

Tuple cross(Tuple a, Tuple b) {
    if (a.isPoint() || b.isPoint())  
        throw std::logic_error("Can't have dot product between points");

    return Tuple::vector(a.y * b.z - a.z * b.y,
                         a.z * b.x - a.x * b.z,
                         a.x * b.y - a.y * b.x);
}