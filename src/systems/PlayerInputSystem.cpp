#include "systems/PlayerInputSystem.hpp"

#include "core/InputManager.hpp"

#include "ecs/Registry.hpp"

#include "ecs/components/PlayerTag.hpp"
#include "ecs/components/Velocity.hpp"

PlayerInputSystem::PlayerInputSystem(
    InputManager& input,
    float baseSpeed)
    : m_input(input),
      m_baseSpeed(baseSpeed)
{}

void PlayerInputSystem::update(
    Registry& reg,
    float /*dt*/)
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

        vel.value = dir.normalized() * m_baseSpeed;
    });
}