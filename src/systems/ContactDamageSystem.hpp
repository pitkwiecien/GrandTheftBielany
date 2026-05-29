#pragma once
#include "systems/ISystem.hpp"

class ContactDamageSystem : public ISystem {
public:
    void update(Registry& reg, float dt) override;
};
