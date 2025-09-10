#pragma once
#include <cmath>
#include <iostream>

struct Vector2 {
    float x, y;

    Vector2();
    Vector2(float x, float y);
    Vector2(const Vector2 &other);

    float length() const;
    float dot(const Vector2 &other) const;

    Vector2 normalize() const;

    Vector2 operator+(const Vector2 &other) const;
    Vector2 operator-(const Vector2 &other) const;
    Vector2 operator/(float num) const;
    Vector2 operator*(float num) const;
    
};

std::ostream &operator<<(std::ostream &out, const Vector2 &other);

