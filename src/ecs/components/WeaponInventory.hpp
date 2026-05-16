#pragma once
#include <vector>

// Aktywne bronie gracza. Każda ma własny stan przeładowania,
// który WeaponSystem odlicza i zeruje przy strzale.
struct WeaponSlot {
    int   weaponId   = 0;
    int   level      = 1;
    float cooldown   = 0.f; // pozostały czas do następnego strzału
};

struct WeaponInventory {
    std::vector<WeaponSlot> slots;
    static constexpr std::size_t kMaxSlots = 6;
};
