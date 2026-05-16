#pragma once
#include "ISystem.hpp"

class CollisionSystem;

// Zamienia pary kolizji na obrażenia:
//  - pocisk vs wróg => obrażenia + zużycie pierce
//  - wróg vs gracz  => obrażenia kontaktowe + nietykalność
// Encje z Health.dead trafiają do queueDestroy w Registry.
class DamageSystem : public ISystem {
public:
    explicit DamageSystem(CollisionSystem& collisions);
    void update(Registry& reg, float dt) override;

private:
    CollisionSystem& m_collisions;
};
