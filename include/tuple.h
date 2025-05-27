#pragma once

struct Tuple {
private:
    Tuple(float x, float y, float z, float w);

public:
    float x, y, z, w;

    static Tuple vector(float x, float y, float z);

    static Tuple point(float x, float y, float z);

    bool isPoint() const;

    Tuple operator * (float scalar) const;

    Tuple operator / (float scalar) const;

    Tuple operator - () const;

    float magnitude() const;

    Tuple normalize() const;

    friend bool operator == (Tuple t1, Tuple t2);

    friend Tuple operator + (Tuple t1, Tuple t2);

    friend Tuple operator - (Tuple t1, Tuple t2);

    friend float dot (Tuple t1, Tuple t2);

    friend Tuple cross(Tuple t1, Tuple t2);
    
};