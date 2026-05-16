#pragma once
#include "ISystem.hpp"

class WeaponDatabase;
class TextureManager;

// Automatyczne strzelanie (rdzeń survivora — gracz nie celuje ręcznie).
// Dla każdej broni odlicza cooldown, po wyzerowaniu szuka celu
// i tworzy encje pocisków wg definicji z WeaponDatabase.
class WeaponSystem : public ISystem {
public:
    WeaponSystem(WeaponDatabase& db, TextureManager& textures);
    void update(Registry& reg, float dt) override;

private:
    WeaponDatabase& m_db;
    TextureManager& m_textures;
};
