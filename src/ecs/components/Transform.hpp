#pragma once
#include "math/Vec2.hpp"

// Pozycja w świecie + obrót (stopnie) do rysowania pocisków itp.
struct Transform {
    Vec2  pos{};
    float rotation = 0.f;
    float scale    = 1.f;
};
