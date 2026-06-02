#include "systems/EnemyAISystem.hpp"
#include "ecs/Registry.hpp"
#include "ecs/Components.hpp"
#include <SDL.h>
#include <cmath>

Entity EnemyAISystem::findPlayer(Registry& reg) const {
    Entity found = kNullEntity;
    reg.view<PlayerTag, Transform>([&](Entity e, PlayerTag&, Transform&) {
        found = e;
    });
    return found;
}

void EnemyAISystem::update(Registry& reg, float dt) {
    Entity player = findPlayer(reg);
    if (!player.valid()) return;

    auto* pt = reg.tryGet<Transform>(player);
    if (!pt) return;

    // Fetch time in seconds to drive the weaving animation
    float timeSec = SDL_GetTicks() / 1000.0f;

    reg.view<EnemyTag, Transform, Velocity>(
        [&](Entity e, EnemyTag&, Transform& t, Velocity& vel) {
            
            // 1. Calculate true 360-degree direction to the player
            Vec2 toPlayer = pt->pos - t.pos;
            float dist = toPlayer.length();
            
            Vec2 desiredDir{0.f, 0.f};
            if (dist > 0.001f) {
                desiredDir = toPlayer / dist;
            }

            // 2. Apply Organic Wobble (Anti-stacking)
            // Get the perpendicular vector to the target direction
            Vec2 perp{-desiredDir.y, desiredDir.x};
            
            // Sine wave oscillates between -1 and 1. We offset the phase using the Entity ID (e.id)
            // so that no two boars follow the exact same zigzag pattern.
            float wobbleAmount = std::sin(timeSec * 4.0f + static_cast<float>(e.id)) * 0.35f;
            
            // Blend the direct pursuit with the side-to-side wobble
            desiredDir = (desiredDir + perp * wobbleAmount).normalized();

            // 3. Calculate intended target speed
            Vec2 targetVel = desiredDir * vel.maxSpeed;

            // 4. Apply Heavy Inertia
            // A lower value makes the boar turn slower (larger turning circle). 
            // 2.5f is a sweet spot for making them feel like a charging animal.
            float turnSpeed = 2.5f; 
            vel.value = Math::lerp(vel.value, targetVel, turnSpeed * dt);
        });
}