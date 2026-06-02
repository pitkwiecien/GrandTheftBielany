#pragma once
#include "ISystem.hpp"

// integruje pozycje: pos += velocity * dt, pilnuje maxSpeed (jesli ustawione w Velocity).
class MovementSystem : public ISystem {
    public:
        void update(Registry& reg, float dt) override;
};
