#pragma once
#include <cmath>
#include <algorithm>

struct Vec2 {
    float x = 0.f;
    float y = 0.f;

    constexpr Vec2() = default;
    constexpr Vec2(float x_, float y_) : x(x_), y(y_) {}

    Vec2  operator+(const Vec2& o) const { return {x + o.x, y + o.y}; }
    Vec2  operator-(const Vec2& o) const { return {x - o.x, y - o.y}; }
    Vec2  operator*(float s)       const { return {x * s, y * s}; }
    Vec2  operator/(float s)       const { return {x / s, y / s}; }
    Vec2& operator+=(const Vec2& o) { x += o.x; y += o.y; return *this; }
    Vec2& operator-=(const Vec2& o) { x -= o.x; y -= o.y; return *this; }
    Vec2& operator*=(float s)       { x *= s;  y *= s;  return *this; }

    float lengthSq() const { return x * x + y * y; }
    float length()   const { return std::sqrt(lengthSq()); }

    Vec2 normalized() const {
        float len = length();
        if (len <= 1e-6f) return {0.f, 0.f};
        return {x / len, y / len};
    }

    static float dot(const Vec2& a, const Vec2& b)      { return a.x * b.x + a.y * b.y; }
    static float distance(const Vec2& a, const Vec2& b)  { return (a - b).length(); }
    static float distanceSq(const Vec2& a, const Vec2& b){ return (a - b).lengthSq(); }
};

namespace Math {

template <typename T>
T clamp(T value, T lo, T hi) { return std::max(lo, std::min(value, hi)); }

inline float lerp(float a, float b, float t) { return a + (b - a) * t; }

inline Vec2 lerp(const Vec2& a, const Vec2& b, float t) {
    return {lerp(a.x, b.x, t), lerp(a.y, b.y, t)};
}

inline float moveTowards(float current, float target, float maxDelta) {
    float diff = target - current;
    if (std::abs(diff) <= maxDelta) return target;
    return current + (diff > 0.f ? maxDelta : -maxDelta);
}

constexpr float kPi = 3.14159f;

inline float toDegrees(float r) { return r * (180.f / kPi); }
inline float toRadians(float d) { return d * (kPi / 180.f); }
inline float angleDeg(const Vec2& v) { return toDegrees(std::atan2(v.y, v.x)); }

inline Vec2 snapTo8Directions(Vec2 dir) {
    if (dir.x == 0.f && dir.y == 0.f) return {1.f, 0.f};
    float angle = std::atan2(dir.y, dir.x);
    float snapped = std::round(angle / (kPi / 4.f)) * (kPi / 4.f);
    return {std::cos(snapped), std::sin(snapped)};
}

} // namespace Math
