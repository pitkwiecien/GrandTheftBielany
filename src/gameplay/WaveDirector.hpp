#pragma once
#include "math/Math.hpp"

// obsluga fali przeciwnikow - fala N, spawnuje N wrogow, kazdy co 2 sekundy
// kazda kolejna fala nastepuje po pokonaniu wrogow z poprzedniej (5s po jej zakonczeniu)
class WaveDirector {
public:
    static constexpr float kSpawnInterval   = 2.f; // s miedzy spawnami w fali
    static constexpr float kAllDeadCooldown = 5.f; // s przerwy po pokonaniu fali

    int update(float dt, int livingEnemies);

    int  currentWave() const { return m_wave; }
    bool isSpawning()  const { return !m_idle; }

    Vec2 randomEdgePos() const;

private:
    int   m_wave         = 1;
    int   m_toSpawn      = 1;
    float m_spawnTimer   = 0.f;
    bool  m_idle         = false;
    float m_allDeadTimer = -1.f;
};
