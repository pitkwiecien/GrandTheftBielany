#pragma once
#include <cmath>
#include <algorithm>

struct Vec2 {
    float x = 0.f;
    float y = 0.f;

    constexpr Vec2() =default;
    constexpr Vec2(float x_, float y_) : x(x_), y(y_) {}

    Vec2 operator+(const Vec2& o) const { return {x + o.x, y + o.y}; }
    Vec2 operator-(const Vec2& o) const { return {x - o.x, y - o.y}; }
    Vec2 operator*(float s) const { return {x * s, y * s}; }
    Vec2 operator/(float s) const { return {x / s, y / s}; }
    Vec2& operator+=(const Vec2& o) { x += o.x; y += o.y; return *this; }

    float lengthSq() const { return x * x + y * y; }
    float length() const { return std::sqrt(lengthSq()); }

    Vec2 normalized() const {
        float len = length();
        if (len <= 1e-6f) return {0.f, 0.f};
        return {x / len, y / len};
    }

    static float distance(const Vec2& a, const Vec2& b) { return (a - b).length(); }
    static float distanceSq(const Vec2& a, const Vec2& b) { return (a - b).lengthSq(); }
};

namespace Math {
    template <typename T>
    T clamp(T value, T lo, T hi) { return std::max(lo, std::min(value, hi)); }

    inline float lerp(float a, float b, float t) {
        return a + (b - a) * t;
    }
    inline Vec2 lerp(const Vec2& a, const Vec2& b, float t) {
        return {lerp(a.x, b.x, t), lerp(a.y, b.y, t)};
    }
}
