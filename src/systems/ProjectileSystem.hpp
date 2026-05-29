#pragma once
#include "systems/ISystem.hpp"

class ProjectileSystem : public ISystem {
public:
    void update(Registry& reg, float dt) override;

private:
    static constexpr float kBulletRadius = 4.f;
};
