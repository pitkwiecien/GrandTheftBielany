#pragma once
#include "ISystem.hpp"

// Integruje pozycję: pos += velocity * dt.
// Pilnuje też maxSpeed (jeśli ustawione w Velocity).
class MovementSystem : public ISystem {
public:
    void update(Registry& reg, float dt) override;
};
