#pragma once
#include "ISystem.hpp"

class AnimationSystem : public ISystem {
public:
    void update(Registry& reg, float dt) override;
};