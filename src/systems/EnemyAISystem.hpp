#pragma once
#include "ISystem.hpp"
#include "ecs/Entity.hpp"

// Prosta AI survivora: każdy wróg idzie wprost na gracza.
// Cel (gracz) wyszukiwany raz na klatkę i cache'owany.
class EnemyAISystem : public ISystem {
public:
    void update(Registry& reg, float dt) override;

private:
    Entity findPlayer(Registry& reg) const;
};
