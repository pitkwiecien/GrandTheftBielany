#pragma once

class Registry;

// Wspólny interfejs systemów. PlayState trzyma listę ISystem
// i woła update() w ustalonej kolejności co klatkę.
class ISystem {
public:
    virtual ~ISystem() = default;
    virtual void update(Registry& reg, float dt) = 0;
};
