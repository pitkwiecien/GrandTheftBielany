#pragma once
#include <unordered_map>
#include <vector>
#include "Weapon.hpp"

// Centralny rejestr definicji broni. Ładowany raz na starcie
// (loadDefaults lub z pliku danych). WeaponSystem pyta o definicje po id.
class WeaponDatabase {
public:
    void registerWeapon(const Weapon& w);
    void loadDefaults();

    const Weapon* get(int id) const;
    const std::vector<Weapon>& all() const { return m_list; }

private:
    std::vector<Weapon>             m_list;
    std::unordered_map<int, std::size_t> m_index; // id -> pozycja w m_list
};
