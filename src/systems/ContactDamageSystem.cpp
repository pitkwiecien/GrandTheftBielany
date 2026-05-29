#include "systems/ContactDamageSystem.hpp"
#include "ecs/Registry.hpp"
#include "ecs/Components.hpp"

void ContactDamageSystem::update(Registry& reg, float dt) {
    Entity player = kNullEntity;
    reg.view<PlayerTag, Transform>([&](Entity e, PlayerTag&, Transform&) {
        player = e;
    });
    if (!player.valid()) return;

    auto* playerHealth    = reg.tryGet<Health>(player);
    auto* playerTransform = reg.tryGet<Transform>(player);
    auto* playerCollider  = reg.tryGet<Collider>(player);
    if (!playerHealth || !playerTransform || !playerCollider) return;
    if (playerHealth->dead) return;

    if (playerHealth->invulnTimer > 0.f)
        playerHealth->invulnTimer = std::max(0.f, playerHealth->invulnTimer - dt);

    reg.view<EnemyTag, Transform, Collider>(
        [&](Entity, EnemyTag& enemy, Transform& t, Collider& c) {
            float dx      = t.pos.x - playerTransform->pos.x;
            float dy      = t.pos.y - playerTransform->pos.y;
            float distSq  = dx * dx + dy * dy;
            float minDist = playerCollider->radius + c.radius;

            if (distSq >= minDist * minDist) return;

            float dist = (distSq > 1e-8f) ? std::sqrt(distSq) : 1.f;
            if (distSq <= 1e-8f) { dx = minDist; dy = 0.f; }
            float overlap = minDist - dist;
            t.pos.x += (dx / dist) * overlap;
            t.pos.y += (dy / dist) * overlap;

            if (playerHealth->invulnTimer <= 0.f) {
                playerHealth->damage(enemy.touchDamage);
                playerHealth->invulnTimer = 1.f;
            }
        });
}
