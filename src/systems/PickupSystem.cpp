#include "systems/PickupSystem.hpp"
#include "ecs/Registry.hpp"
#include "ecs/Components.hpp"

void PickupSystem::update(Registry& registry, float) {
    Entity playerEntity{};

    registry.view<PlayerTag, Transform>(
        [&](Entity entity, PlayerTag&, Transform&) {
            playerEntity = entity;
        });

    if (!playerEntity.valid()) {
        return;
    }

    auto* playerTransform = registry.tryGet<Transform>(playerEntity);
    auto* playerHealth = registry.tryGet<Health>(playerEntity);

    if (!playerTransform || !playerHealth || playerHealth->dead) {
        return;
    }

    registry.view<BeerPickup, Transform>(
        [&](Entity entity, BeerPickup& beerPickup, Transform& transform) {
            float distance = Vec2::distance(playerTransform->pos, transform.pos);

            if (distance < beerPickup.radius + 16.f) {
                playerHealth->heal(beerPickup.healAmount);
                registry.queueDestroy(entity);
            }
        });
}