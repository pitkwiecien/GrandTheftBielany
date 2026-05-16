#pragma once
#include "math/Vec2.hpp"

// Prędkość w jednostkach świata na sekundę.
// MovementSystem robi: transform.pos += velocity.value * dt.
struct Velocity {
    Vec2  value{};
    float maxSpeed = 0.f; // 0 = bez limitu
};
