#pragma once
#include <string>

// Statyczna definicja broni (dane, nie stan w grze).
// Stan działania (cooldown) trzyma WeaponInventory na encji gracza.
enum class TargetingMode {
    Nearest,      // najbliższy wróg
    Random,       // losowy w zasięgu
    Forward,      // kierunek ruchu gracza
    Surround      // pociski na wszystkie strony
};

struct Weapon {
    int          id   = 0;
    std::string  name;
    float        baseDamage     = 1.f;
    float        baseCooldown   = 1.f;  // sekundy między strzałami
    float        projectileSpeed = 300.f;
    int          projectileCount = 1;
    int          pierce          = 0;
    float        projectileLifetime = 2.f;
    TargetingMode targeting = TargetingMode::Nearest;
    std::string  projectileTexture;

    // Skalowanie statystyk wraz z poziomem broni.
    float damageAtLevel(int level)   const { return baseDamage   * (1.f + 0.2f * (level - 1)); }
    float cooldownAtLevel(int level) const { return baseCooldown * (1.f - 0.05f * (level - 1)); }
};
