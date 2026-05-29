#include "systems/SeparationSystem.hpp"
#include "ecs/Registry.hpp"
#include "ecs/components/Transform.hpp"
#include "ecs/components/Collider.hpp"
#include "ecs/components/EnemyTag.hpp"
#include <vector>
#include <cmath>

void SeparationSystem::update(Registry& reg, float /*dt*/) {
    struct Entry { Transform* t; float radius; };
    std::vector<Entry> enemies;

    reg.view<EnemyTag, Transform, Collider>(
        [&](Entity, EnemyTag&, Transform& t, Collider& c) {
            enemies.push_back({&t, c.radius});
        });

    for (std::size_t i = 0; i < enemies.size(); ++i) {
        for (std::size_t j = i + 1; j < enemies.size(); ++j) {
            auto& a = enemies[i];
            auto& b = enemies[j];

            float dx = a.t->pos.x - b.t->pos.x;
            float dy = a.t->pos.y - b.t->pos.y;
            float distSq = dx * dx + dy * dy;
            float minDist = (a.radius + b.radius) * 0.6f;

            if (distSq >= minDist * minDist) continue;

            float dist = (distSq > 1e-8f) ? std::sqrt(distSq) : 1.f;
            if (distSq <= 1e-8f) { dx = minDist; dy = 0.f; }

            float overlap = (minDist - dist) * 0.5f;
            float nx = dx / dist;
            float ny = dy / dist;

            a.t->pos.x += nx * overlap;
            a.t->pos.y += ny * overlap;
            b.t->pos.x -= nx * overlap;
            b.t->pos.y -= ny * overlap;
        }
    }
}
