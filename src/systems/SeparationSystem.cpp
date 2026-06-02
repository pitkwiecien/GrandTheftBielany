#include "systems/SeparationSystem.hpp"
#include "ecs/Components.hpp"
#include "ecs/Registry.hpp"
#include <vector>
#include <cmath>

void SeparationSystem::update(Registry& reg, float dt) {
    struct Entry { Transform* t; float radius; };
    std::vector<Entry> enemies;

    reg.view<EnemyTag, Transform, Collider>(
        [&](Entity, EnemyTag&, Transform& t, Collider& c) {
            enemies.push_back({&t, c.radius});
        });

    int n = static_cast<int>(enemies.size());
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
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
