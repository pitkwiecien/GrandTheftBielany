#pragma once
#include <algorithm>
#include "Vec2.hpp"

namespace MathUtils {

template <typename T>
T clamp(T value, T lo, T hi) {
    return std::max(lo, std::min(value, hi));
}

inline float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

inline Vec2 lerp(const Vec2& a, const Vec2& b, float t) {
    return {lerp(a.x, b.x, t), lerp(a.y, b.y, t)};
}

// Przesuwa "current" w stronę "target" o nie więcej niż maxDelta.
inline float moveTowards(float current, float target, float maxDelta) {
    float diff = target - current;
    if (std::abs(diff) <= maxDelta) return target;
    return current + (diff > 0.f ? maxDelta : -maxDelta);
}

constexpr float kPi = 3.14159265358979323846f;

inline float toDegrees(float radians) { return radians * (180.f / kPi); }
inline float toRadians(float degrees) { return degrees * (kPi / 180.f); }

// Kąt wektora w stopniach (przydatne do obracania pocisków).
inline float angleDeg(const Vec2& v) {
    return toDegrees(std::atan2(v.y, v.x));
}

} // namespace MathUtils
