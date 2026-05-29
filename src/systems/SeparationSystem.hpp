#pragma once
#include "systems/ISystem.hpp"

class SeparationSystem : public ISystem {
public:
    void update(Registry& reg, float dt) override;
};
