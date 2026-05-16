#pragma once
#include "ISystem.hpp"

// Obsługuje znajdźki: w promieniu magnesu lecą do gracza,
// przy kontakcie aplikują efekt (XP, leczenie, magnes globalny).
// XP przekazuje do PlayerTag (awans liczy ExperienceSystem).
class PickupSystem : public ISystem {
public:
    void update(Registry& reg, float dt) override;
};
