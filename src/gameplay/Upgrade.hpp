#pragma once
#include <string>
#include <functional>

struct PlayerStats;
struct StatModifiers;
struct WeaponInventory;

// Pojedyncze ulepszenie do wyboru po awansie poziomu.
// apply() dostaje wszystko, co może chcieć zmienić:
// statystyki bazowe, modyfikatory, ekwipunek broni.
struct UpgradeContext {
    PlayerStats*    stats     = nullptr;
    StatModifiers*  mods      = nullptr;
    WeaponInventory* weapons  = nullptr;
};

enum class UpgradeRarity { Common, Rare, Epic };

struct Upgrade {
    int           id   = 0;
    std::string   name;
    std::string   description;
    UpgradeRarity rarity   = UpgradeRarity::Common;
    int           maxStacks = 5;
    int           taken     = 0; // ile razy już wzięte
    std::string   iconTexture;

    std::function<void(UpgradeContext&)> apply;

    bool available() const { return taken < maxStacks; }
};
