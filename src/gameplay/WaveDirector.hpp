#pragma once
#include <vector>
#include "EnemyType.hpp"

// Rdzeń survivora: steruje tym, co i jak gęsto się spawnuje
// w funkcji czasu gry. Tempo i pula wrogów rosną z czasem,
// co jakiś czas wyzwala "elitarną" falę lub bossa.
class WaveDirector {
public:
    void loadDefaults();
    void registerEnemy(const EnemyType& type);

    // Zwraca liczbę wrogów do zespawnowania w tej klatce (akumulator).
    int  enemiesToSpawn(float gameTime, float dt);

    // Losuje typ wroga dostępny dla danego czasu gry (wg wag).
    const EnemyType* pickEnemy(float gameTime) const;

    bool isBossTime(float gameTime) const;
    const EnemyType* currentBoss(float gameTime) const;

private:
    float spawnRate(float gameTime) const; // wrogów / sekundę

    std::vector<EnemyType> m_enemies;
    std::vector<EnemyType> m_bosses;
    float m_accumulator   = 0.f;
    float m_lastBossTime  = -1.f;
};
