#include "systems/EnemyAISystem.hpp"
#include <cmath>
#include "ecs/Registry.hpp"
#include "ecs/components/Transform.hpp"
#include "ecs/components/Velocity.hpp"
#include "ecs/components/EnemyTag.hpp"
#include "ecs/components/PlayerTag.hpp"

static Vec2 dirToPlayer(const Vec2& from, const Vec2& to) {
    float dx = to.x - from.x;
    float dy = to.y - from.y;

    float ax = std::abs(dx);
    float ay = std::abs(dy);

    float sx = (dx > 0.f) ? 1.f : (dx < 0.f ? -1.f : 0.f);
    float sy = (dy > 0.f) ? 1.f : (dy < 0.f ? -1.f : 0.f);

    if (ax > ay * 2.f) sy = 0.f;
    else if (ay > ax * 2.f) sx = 0.f;
    Vec2 dir{sx, sy};
    return dir.normalized();
}

Entity EnemyAISystem::findPlayer(Registry& reg) const {
    Entity found = kNullEntity;
    reg.view<PlayerTag, Transform>(
        [&](Entity e, PlayerTag&, Transform&) {
            found = e;
        });
    return found;
}

void EnemyAISystem::update(Registry& reg, float /*dt*/) {
    Entity player = findPlayer(reg);
    if (!player.valid()) return;

    auto* playerTransform = reg.tryGet<Transform>(player);
    if (!playerTransform) return;

    reg.view<EnemyTag, Transform, Velocity>(
        [&](Entity /*e*/,
            EnemyTag& enemy,
            Transform& t,
            Velocity& vel)
    {
        Vec2 dir = dirToPlayer(t.pos, playerTransform->pos);
        vel.value = dir * vel.maxSpeed;
    });
}