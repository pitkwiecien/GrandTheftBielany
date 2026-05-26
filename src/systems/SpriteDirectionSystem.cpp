#include "systems/SpriteDirectionSystem.hpp"
#include <cmath>
#include "ecs/Registry.hpp"
#include "ecs/components/Velocity.hpp"
#include "ecs/components/DirectionComp.hpp"
#include "ecs/components/SpriteComp.hpp"
#include "ecs/components/AnimationComp.hpp"

static Direction8 vecToDir8(float vx, float vy) {
    float angle = std::atan2(vy, vx);
    if (angle < 0.f) angle += 2.f * 3.14159265f;

    constexpr float kStep = 3.14159265f / 4.f;
    int s = static_cast<int>((angle + kStep * 0.5f) / kStep) % 8;

    switch (s) {
        case 0: return Direction8::East;
        case 1: return Direction8::SouthEast;
        case 2: return Direction8::South;
        case 3: return Direction8::SouthWest;
        case 4: return Direction8::West;
        case 5: return Direction8::NorthWest;
        case 6: return Direction8::North;
        case 7: return Direction8::NorthEast;
        default: return Direction8::South;
    }
}

static bool facingRight(Direction8 d) {
    return d == Direction8::East
        || d == Direction8::NorthEast
        || d == Direction8::SouthEast;
}

void SpriteDirectionSystem::update(Registry& reg, float /*dt*/) {
    reg.view<Velocity, DirectionComp, SpriteComp>(
        [&](Entity e, Velocity& vel, DirectionComp& dir, SpriteComp& sprite)
    {
        bool isMoving = vel.value.lengthSq() >= 1.f;

        if (isMoving) {
            dir.facing = vecToDir8(vel.value.x, vel.value.y);
        }

        SDL_Texture* tex = isMoving ? 
            dir.runTextures[static_cast<int>(dir.facing)] : 
            dir.idleTextures[static_cast<int>(dir.facing)];

        if (tex) {
            sprite.texture = tex;
        }

        if (auto* anim = reg.tryGet<AnimationComp>(e)) {
            anim->isPlaying = isMoving; 
        }
    });

    reg.view<Velocity, SpriteComp>(
        [&](Entity e,
            Velocity& vel,
            SpriteComp& sprite)
    {
        if (reg.has<DirectionComp>(e))
            return;

        if (vel.value.lengthSq() < 1.f)
            return;

        Direction8 dir = vecToDir8(vel.value.x, vel.value.y);
        sprite.flipHorizontal = facingRight(dir);
    });
}