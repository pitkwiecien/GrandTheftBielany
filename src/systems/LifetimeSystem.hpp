#pragma once
#include "ISystem.hpp"

// Odlicza ProjectileTag.lifetime i kolejkuje do usunięcia
// pociski, które przeżyły za długo (nie trafiły nic).
class LifetimeSystem : public ISystem {
public:
    void update(Registry& reg, float dt) override;
};
