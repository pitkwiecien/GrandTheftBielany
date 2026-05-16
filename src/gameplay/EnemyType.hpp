#pragma once
#include <string>

// Definicja archetypu wroga. SpawnSystem tworzy z tego encje.
struct EnemyType {
    int         id   = 0;
    std::string name;
    float       maxHealth   = 3.f;
    float       moveSpeed   = 50.f;
    float       touchDamage = 1.f;
    float       xpReward    = 1.f;
    float       colliderRadius = 10.f;
    std::string texture;

    // Czas (sekundy od startu gry), od którego ten wróg może się pojawiać.
    float       minSpawnTime = 0.f;
    // Waga losowania względem innych dostępnych typów.
    float       spawnWeight  = 1.f;
};
