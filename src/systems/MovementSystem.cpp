#include "systems/MovementSystem.hpp"
#include "ecs/Components.hpp"
#include "ecs/Registry.hpp"

void MovementSystem::update(Registry& reg, float dt)
{
    reg.view<Transform, Velocity>(
        [&](Entity e,
            Transform& t,
            Velocity& v) {
        if (v.maxSpeed > 0.f) {
            float len = v.value.length();
            if (len > v.maxSpeed)
                v.value = v.value.normalized() * v.maxSpeed;
        }
        t.pos += v.value * dt;
    });
}