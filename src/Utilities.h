#pragma once
#include <cmath>
#include <iostream>
#include <vector>
#include <chrono>

struct Timer {
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    std::chrono::duration<float> duration;
    Timer() {
        start = std::chrono::steady_clock::now();
    }
    ~Timer() {
        end = std::chrono::steady_clock::now();
        duration = end - start;
        duration *= 1000;
        std::cout << "TIMER: Time Elapsed - " << duration.count() << "ms\n";
    }

};
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
    Vector2 &operator+=(const Vector2 &other);
    
};

std::ostream &operator<<(std::ostream &out, const Vector2 &other);

