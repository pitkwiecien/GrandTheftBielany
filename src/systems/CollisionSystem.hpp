#pragma once
#include "ISystem.hpp"
#include "ecs/Entity.hpp"
#include <vector>

// Wykrywa kolizje kołowe i odkłada pary do bufora,
// który czyta DamageSystem/PickupSystem. Używa siatki przestrzennej
// (spatial hash), bo naiwne n^2 przy setkach wrogów zabija FPS.
class CollisionSystem : public ISystem {
public:
    struct CollisionPair { Entity a; Entity b; };

    void update(Registry& reg, float dt) override;

    const std::vector<CollisionPair>& pairs() const { return m_pairs; }

private:
    void rebuildGrid(Registry& reg);

    std::vector<CollisionPair> m_pairs;
    float m_cellSize = 64.f;
};
