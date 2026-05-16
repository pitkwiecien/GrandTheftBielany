#pragma once
#include "ISystem.hpp"

// Sprawdza, czy XP gracza przekroczyło próg.
// Jeśli tak: poziom++, nowy próg, pendingLevelUps++.
// PlayState po update sprawdza pendingLevelUps i wrzuca LevelUpState.
class ExperienceSystem : public ISystem {
public:
    void update(Registry& reg, float dt) override;

private:
    // Krzywa progu XP — rosnąca z poziomem.
    static float xpThreshold(int level);
};
