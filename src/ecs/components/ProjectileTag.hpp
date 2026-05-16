#pragma once
#include "ecs/Entity.hpp"

// Znacznik pocisku wystrzelonego przez broń.
// pierce = ilu wrogów może przebić zanim zniknie.
struct ProjectileTag {
    float  damage   = 1.f;
    int    pierce   = 0;
    float  lifetime = 2.f;   // sekundy do automatycznego zniknięcia
    Entity owner = kNullEntity; // kto wystrzelił (by nie ranił siebie)
};
