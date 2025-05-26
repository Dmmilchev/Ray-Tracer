#pragma once

struct Tuple {
private:
    Tuple(float x, float y, float z, float w);

public:
    float x, y, z, w;

    static Tuple vector(float x, float y, float z);

    static Tuple point(float x, float y, float z);

    bool isPoint() const;

    Tuple operator * (float scalar);

    friend Tuple operator + (Tuple t1, Tuple t2);

    friend Tuple operator - (Tuple t1, Tuple t2);
    
};