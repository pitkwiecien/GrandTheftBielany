#pragma once
#include <vector>
#include "Upgrade.hpp"

// Pula wszystkich ulepszeń. Po awansie losuje kilka kart
// (z uwzględnieniem rzadkości i wyczerpanych stacków),
// LevelUpState pokazuje je graczowi, wybraną aplikuje przez apply().
class UpgradePool {
public:
    void loadDefaults();
    void registerUpgrade(Upgrade u);

    // Losuje 'count' różnych dostępnych ulepszeń (zwykle 3-4).
    std::vector<Upgrade*> roll(int count);

    // Wywoływane po wyborze gracza — zwiększa licznik 'taken'.
    void markTaken(int upgradeId);

private:
    std::vector<Upgrade> m_all;

    float rarityWeight(UpgradeRarity r) const;
};
