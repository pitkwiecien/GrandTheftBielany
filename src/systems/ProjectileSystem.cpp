#include "systems/ProjectileSystem.hpp"
#include "ecs/Registry.hpp"
#include "ecs/Components.hpp"
#include "util/Random.hpp"
#include <vector>

void ProjectileSystem::update(Registry& reg, float dt) {
    struct EnemyEntry { Entity e; Transform* t; float radius; Health* h; };
    std::vector<EnemyEntry> enemies;
    reg.view<EnemyTag, Transform, Collider, Health>(
        [&](Entity e, EnemyTag&, Transform& t, Collider& c, Health& h) {
            enemies.push_back({e, &t, c.radius, &h});
        });

    reg.view<ProjectileTag, Transform>(
        [&](Entity e, ProjectileTag& p, Transform& t) {
            p.lifetime -= dt;
            if (p.lifetime <= 0.f) {
                reg.queueDestroy(e);
                return;
            }

            for (auto& en : enemies) {
                if (en.h->dead) continue;
                float dist = Vec2::distance(t.pos, en.t->pos);
                if (dist < en.radius + kBulletRadius) {
                    bool isCrit = Random::chance(kCritChance);
                    en.h->damage(p.damage, isCrit);
                    reg.queueDestroy(e);
                    return;
                }
            }
        });
}