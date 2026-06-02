#include "systems/PlayerInputSystem.hpp"
#include "core/InputManager.hpp"
#include "ecs/Registry.hpp"
#include "ecs/Components.hpp"

PlayerInputSystem::PlayerInputSystem(InputManager& input, float baseSpeed)
    : m_input(input), m_baseSpeed(baseSpeed) {}

void PlayerInputSystem::update(Registry& reg, float dt) {
    reg.view<PlayerTag, Velocity, DirectionComp>(
        [&](Entity, PlayerTag& tag, Velocity& vel, DirectionComp& dirComp) {
            
            Vec2 dir{0.f, 0.f};

            if (m_input.isDown(SDL_SCANCODE_W) || m_input.isDown(SDL_SCANCODE_UP))    dir.y -= 1.f;
            if (m_input.isDown(SDL_SCANCODE_S) || m_input.isDown(SDL_SCANCODE_DOWN))  dir.y += 1.f;
            if (m_input.isDown(SDL_SCANCODE_A) || m_input.isDown(SDL_SCANCODE_LEFT))  dir.x -= 1.f;
            if (m_input.isDown(SDL_SCANCODE_D) || m_input.isDown(SDL_SCANCODE_RIGHT)) dir.x += 1.f;

            // moving
            // natural acceleration
            if (!tag.isAiming) {
                Vec2 target = dir.normalized() * m_baseSpeed;
                float speedRatio = Math::clamp(vel.value.length() / m_baseSpeed, 0.f, 1.f);
                float dynamicSmoothing = (dir.x == 0.f && dir.y == 0.f)
                    ? 15.f
                    : 3.f + 15.f * speedRatio * speedRatio;
                vel.value = Math::lerp(vel.value, target, dynamicSmoothing * dt);

                // eliminate gliding
                if (vel.value.lengthSq() < 0.5f) {
                    vel.value = Vec2{0.f, 0.f};
                }
            } else {
                // when stopped allow changing directions 
                // ( only shooting allows this )
                vel.value = Vec2{0.f, 0.f};

                if (dir.lengthSq() > 0.f) {
                    if (dir.x == 0.f && dir.y < 0.f)        dirComp.facing = Direction8::North;
                    else if (dir.x > 0.f && dir.y < 0.f)    dirComp.facing = Direction8::NorthEast;
                    else if (dir.x > 0.f && dir.y == 0.f)   dirComp.facing = Direction8::East;
                    else if (dir.x > 0.f && dir.y > 0.f)    dirComp.facing = Direction8::SouthEast;
                    else if (dir.x == 0.f && dir.y > 0.f)   dirComp.facing = Direction8::South;
                    else if (dir.x < 0.f && dir.y > 0.f)    dirComp.facing = Direction8::SouthWest;
                    else if (dir.x < 0.f && dir.y == 0.f)   dirComp.facing = Direction8::West;
                    else if (dir.x < 0.f && dir.y < 0.f)    dirComp.facing = Direction8::NorthWest;
                }
            }
        });
}