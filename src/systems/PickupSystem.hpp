#pragma once
#include "systems/ISystem.hpp"

class PickupSystem : public ISystem {
    public:
        void update(Registry& reg, float dt) override;
};