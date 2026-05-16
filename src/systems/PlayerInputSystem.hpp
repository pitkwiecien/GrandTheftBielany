#pragma once
#include "ISystem.hpp"

class InputManager;

// Czyta WSAD/strzałki i ustawia Velocity gracza.
// Uwzględnia StatModifiers.moveSpeedMult.
class PlayerInputSystem : public ISystem {
public:
    explicit PlayerInputSystem(InputManager& input, float baseSpeed = 150.f);
    void update(Registry& reg, float dt) override;

private:
    InputManager& m_input;
    float         m_baseSpeed;
};
