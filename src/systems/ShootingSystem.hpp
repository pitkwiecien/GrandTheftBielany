#pragma once
#include "systems/ISystem.hpp"
#include <SDL.h>

class InputManager;

class ShootingSystem : public ISystem {
public:
    ShootingSystem(const InputManager& input, SDL_Texture* bulletTex);
    void update(Registry& reg, float dt) override;

private:
    const InputManager& m_input;
    SDL_Texture*        m_bulletTex;
    float               m_cooldown = 0.f;

    static constexpr float kFireRate     = 1.f / 3.f; // 3 strzały/s
    static constexpr float kBulletSpeed  = 420.f;
    static constexpr float kBulletDamage = 5.f;
    static constexpr float kBulletLife   = 2.f;
};
