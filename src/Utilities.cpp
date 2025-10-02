#include "Utilities.h"


//Vector2 class constructors
Vector2::Vector2() : x(0), y(0) {}
Vector2::Vector2(float x, float y) : x(x), y(y) {}
Vector2::Vector2(const Vector2 &other) : x(other.x), y(other.y) {}

//Vector2 class member functions
float Vector2::length() const {
    return sqrt(x*x + y*y);
}
Vector2 Vector2::normalize() const {
    float len = length();
    if (len == 0) return Vector2();
    return Vector2(x/len, y/len);
}
Vector2 Vector2::operator+(const Vector2 &other) const {
    return Vector2(x + other.x, y + other.y);
}
Vector2 Vector2::operator-(const Vector2 &other) const {
    return Vector2(x - other.x, y - other.y);
}
Vector2 Vector2::operator/(float num) const {
    if (num == 0) {
        std::cerr << "ERROR: DIVISION BY ZERO" << std::endl;
        return *this;
    }
    return Vector2(x/num, y/num);
}
Vector2 Vector2::operator/(double num) const {
    if (num == 0) {
        std::cerr << "ERROR: DIVISION BY ZERO" << std::endl;
        return *this;
    }
    return Vector2(x/num, y/num);
}
Vector2 Vector2::operator*(float num) const {
    if (num == 0) {
        return Vector2();
    }
    return Vector2(x * num, y * num);
}
Vector2 Vector2::operator*(double num) const {
    return Vector2(x * num, y * num);
}
Vector2 &Vector2::operator+=(const Vector2 &other) {
    x += other.x;
    y += other.y;
    return *this;
}


//ostream
std::ostream &operator<<(std::ostream &out, const Vector2 &other) {
    return out << "(" << other.x << "," << other.y << ")"; 
}

Vector2 project(const Vector2 &u, const Vector2 &V) {
    float length = u.length();
    if (length == 0) return Vector2();
    return u * (dot(u,V) / (length * length));
}
float projectLength(const Vector2 &u, const Vector2 &V) {
    return dot(V, u)/u.length();
}
float dot(const Vector2 v1, const Vector2 v2) {
    return v1.x * v2.x + v1.y * v2.y;
}
float distance(const Vector2 v1, const Vector2 v2) {
    return abs((v1 - v2).length());
}
float max(float a, float b) {
    return a > b ? a : b;
}
int max(int a, int b) {
    return a > b ? a : b;
}
float min(float a, float b) {
    return a < b ? a : b;
}
int min(int a, int b) {
    return a < b ? a : b;
}
float abs(float v) {
    return v >= 0 ? v : -v;
}
float clamp(float val, float min, float max) {
    if (val < min) return min;
    if (val > max) return max;
    return val;
}