#include "systems/PlayerInputSystem.hpp"

#include "core/InputManager.hpp"

#include "ecs/Registry.hpp"

#include "ecs/components/PlayerTag.hpp"
#include "ecs/components/Velocity.hpp"
#include "math/MathUtils.hpp"

PlayerInputSystem::PlayerInputSystem(
    InputManager& input,
    float baseSpeed)
    : m_input(input),
      m_baseSpeed(baseSpeed)
{}

void PlayerInputSystem::update(
    Registry& reg,
    float dt)
{
    reg.view<PlayerTag, Velocity>(
        [&](Entity /*e*/,
            PlayerTag&,
            Velocity& vel)
    {
        Vec2 dir{};

        if (m_input.isDown(SDL_SCANCODE_W) ||
            m_input.isDown(SDL_SCANCODE_UP))    dir.y -= 1.f;

        if (m_input.isDown(SDL_SCANCODE_S) ||
            m_input.isDown(SDL_SCANCODE_DOWN))  dir.y += 1.f;

        if (m_input.isDown(SDL_SCANCODE_A) ||
            m_input.isDown(SDL_SCANCODE_LEFT))  dir.x -= 1.f;

        if (m_input.isDown(SDL_SCANCODE_D) ||
            m_input.isDown(SDL_SCANCODE_RIGHT)) dir.x += 1.f;

        Vec2 targetVelocity = dir.normalized() * m_baseSpeed;
        
        float currentSpeed = vel.value.length();
        float speedRatio = currentSpeed / m_baseSpeed;

        speedRatio = MathUtils::clamp(speedRatio, 0.f, 1.f);

        float minSmooth = 3.f;
        float maxSmooth = 18.f;

        float dynamicSmoothing = minSmooth + (maxSmooth - minSmooth) * (speedRatio * speedRatio);
        if (dir.x == 0.f && dir.y == 0.f) {
            dynamicSmoothing = 15.f; 
        }
        vel.value = MathUtils::lerp(vel.value, targetVelocity, dynamicSmoothing * dt);
    });
}