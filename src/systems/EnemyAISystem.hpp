#pragma once
#include "ISystem.hpp"
#include "ecs/Entity.hpp"

class EnemyAISystem : public ISystem {
public:
    void update(Registry& reg, float dt) override;

private:
    Entity findPlayer(Registry& reg) const;
};