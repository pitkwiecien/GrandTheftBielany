#pragma once
#include "ISystem.hpp"

class SpriteDirectionSystem : public ISystem {
public:
    void update(Registry& reg, float dt) override;
};