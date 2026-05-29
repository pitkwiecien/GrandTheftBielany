#include "systems/PlayerInputSystem.hpp"
#include "core/InputManager.hpp"
#include "ecs/Registry.hpp"
#include "ecs/Components.hpp"

PlayerInputSystem::PlayerInputSystem(InputManager& input, float baseSpeed)
    : m_input(input), m_baseSpeed(baseSpeed) {}

void PlayerInputSystem::update(Registry& reg, float dt) {
    reg.view<PlayerTag, Velocity>(
        [&](Entity, PlayerTag&, Velocity& vel) {
            Vec2 dir{};
            if (m_input.isDown(SDL_SCANCODE_W) || m_input.isDown(SDL_SCANCODE_UP))    dir.y -= 1.f;
            if (m_input.isDown(SDL_SCANCODE_S) || m_input.isDown(SDL_SCANCODE_DOWN))  dir.y += 1.f;
            if (m_input.isDown(SDL_SCANCODE_A) || m_input.isDown(SDL_SCANCODE_LEFT))  dir.x -= 1.f;
            if (m_input.isDown(SDL_SCANCODE_D) || m_input.isDown(SDL_SCANCODE_RIGHT)) dir.x += 1.f;

            Vec2 target = dir.normalized() * m_baseSpeed;

            float speedRatio      = Math::clamp(vel.value.length() / m_baseSpeed, 0.f, 1.f);
            float dynamicSmoothing = (dir.x == 0.f && dir.y == 0.f)
                ? 15.f
                : 3.f + 15.f * speedRatio * speedRatio;

            vel.value = Math::lerp(vel.value, target, dynamicSmoothing * dt);
            if (vel.value.lengthSq() < 0.5f)
                vel.value = {};
        });
}
